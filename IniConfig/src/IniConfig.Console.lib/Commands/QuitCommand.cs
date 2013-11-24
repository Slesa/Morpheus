using System.Collections.Generic;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class QuitCommand : IMenuCommand
    {
        public QuitCommand()
        {
            Shortcut = "q";
            Description = Strings.QuitCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var result = nextToken;

            environment.QuitProgram = true;
/*
            if (environment.InTestMode && fileName == "q")
            {
                result.Add(fileName);
                fileName = string.Empty;
            }

            if (string.IsNullOrEmpty(fileName))
            {
                environment.Out.WriteLine("No filename given");
                return result;
            }
*/

            return result;
        }
    }
}