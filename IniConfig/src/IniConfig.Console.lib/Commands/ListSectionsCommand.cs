using System.Collections.Generic;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class ListSectionsCommand : IMenuCommand
    {
        public ListSectionsCommand()
        {
            Shortcut = "ls";
            Description = Strings.ListSectionsCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var result = nextToken;

            if (environment.IniFile == null)
            {
                environment.Out.WriteLine(Strings.Warning_NoFileLoaded);
                return result;
            }

            foreach (var section in environment.IniFile.Sections)
            {
                foreach(var remark in section.Remarks)
                    environment.Out.WriteLine(string.Format("// {0}", remark));
                environment.Out.WriteLine(string.Format("[{0}]", section.Name));
            }
            return result;
        }
    }
}