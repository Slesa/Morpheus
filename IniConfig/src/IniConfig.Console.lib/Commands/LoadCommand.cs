using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;

namespace IniConfig.Console.lib.Commands
{
    public class LoadCommand : IMenuCommand
    {
        public LoadCommand()
        {
            Shortcut = "l";
            Description = "Load configuration file";
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var fileName = nextToken.Head();
            var result = nextToken.Tail().ToList();
            
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
            return result;
        }
    }
}