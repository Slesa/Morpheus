using System.Collections.Generic;
using System.IO;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class SaveCommand : IMenuCommand
    {
        public SaveCommand()
        {
            Shortcut = "s";
            Description = Strings.SaveCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            //var fileName = nextToken.Head();
            var result = nextToken; //.Tail().ToList();

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

            try
            {
                //environment.IniFile.Save();
            }
/*
            catch (FileNotFoundException)
            {
                environment.Out.WriteLine("File not found");
                return result;
            }
*/
            catch (DirectoryNotFoundException)
            {
                environment.Out.WriteLine("Part of the file path not found");
                return result;
            }
            return result;
        }
    }
}