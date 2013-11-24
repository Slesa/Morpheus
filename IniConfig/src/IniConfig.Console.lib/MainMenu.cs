using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.lib;

namespace IniConfig.Console.lib
{
    public class MainMenu
    {
        readonly AppEnvironment _environment;
        readonly List<IMenuCommand> _commands = new List<IMenuCommand>();

        public MainMenu(IInput input, IOutput output)
        {
            _environment = new AppEnvironment(input, output);
            RegisterCommands();
        }

        public void Run()
        {
            _environment.Out.WriteLine(string.Format("IniConfig console interface, version {0}", AppVersion.Version));

            _environment.QuitProgram = false;
            while (!_environment.QuitProgram)
            {
                PrintPrompt();
                var input = _environment.In.ReadLine();
                _environment.Out.WriteLine();
                var tokens = NextToken(input).ToList();

                while(true)
                {
                    var token = tokens.Head();
                    if (string.IsNullOrEmpty(token)) break;
                    tokens = tokens.Tail().ToList();

                    var command = _commands.FirstOrDefault(x => x.Shortcut == token);
                    if (command != null)
                    {
                        tokens = command.Execute(tokens, _environment);
                        continue;
                    }
                    switch (token)
                    {
                        case "?":
                            PrintHelp(); continue;
                    }
                    _environment.Out.WriteLine(string.Format("Unknown command {0}", token));
                }
            }
        }

        internal void SetIsInTestMode() { _environment.InTestMode = true; }


        void RegisterCommands()
        {
            _commands.Add(new QuitCommand());
            _commands.Add(new LoadCommand());
            _commands.Add(new SaveCommand());
            _commands.Add(new ListSectionsCommand());
            _commands.Add(new CreateSectionCommand());
            _commands.Add(new RemoveSectionCommand());
            _commands.Add(new ListEntriesCommand());
            _commands.Add(new CreateEntryCommand());
            _commands.Add(new RemoveEntryCommand());
        }


        IEnumerable<string> NextToken(string input)
        {
            return input.Split(' ');
        }

        void PrintPrompt()
        {
            var fileName = _environment.IniFile == null ? "<no file>" : _environment.IniFile.FileName;
            _environment.Out.Write(string.Format("[{0}] ? ", fileName));
        }

        void PrintHelp()
        {
            _environment.Out.WriteLine("Syntax:");

            PrintHelpLine("?", "Print help");
            foreach (var command in _commands.OrderBy(x => x.Shortcut))
            {
                PrintHelpLine(command.Shortcut, command.Description);
            }
        }

        void PrintHelpLine(string shortcut, string description)
        {
            _environment.Out.WriteLine(string.Format("  {0}\t\t\t\t{1}", shortcut, description));
        }
    }
}