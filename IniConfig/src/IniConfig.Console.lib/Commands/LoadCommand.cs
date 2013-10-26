using System.Collections.Generic;
using System.IO;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.lib;

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

            try
            {
                var inifile = IniFile.LoadFrom(fileName);
                environment.IniFile = inifile;
            }
            catch (FileNotFoundException)
            {
                environment.Out.WriteLine("File not found");
                return result;
            }
            catch (DirectoryNotFoundException)
            {
                environment.Out.WriteLine("Part of the file path not found");
                return result;
            }
            return result;
        }
    }
}