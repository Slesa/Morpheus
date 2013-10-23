using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.lib;

namespace IniConfig.Console.lib
{
    public class MainMenu
    {
        readonly IInput _in;
        readonly IOutput _out;

        public MainMenu(IInput input, IOutput output)
        {
            _in = input;
            _out = output;
        }

        public void Run()
        {
            _out.WriteLine(string.Format("IniConfig console interface, version {0}", AppVersion.Version));

            var quit = false;
            while (!quit)
            {
                _out.Write("[<no file>] ? ");
                var input = _in.ReadLine();
                foreach(var command in NextToken(input))
                {
                    switch (command)
                    {
                        case "?":
                            PrintHelp(); break;
                        case "q":
                            quit = true; break;
                    }
                }
            }
        }

        IEnumerable<string> NextToken(string input)
        {
            return input.Split(' ');
        }

        public void PrintHelp()
        {
            _out.WriteLine("?                               Print help");
            _out.WriteLine("q                               Quit program");
        }
    }
}