using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class RemoveEntryCommand : IMenuCommand
    {
        public RemoveEntryCommand()
        {
            Shortcut = "re";
            Description = Strings.RemoveEntryCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }
        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var sectionName = nextToken.Head();
            var result = nextToken.Tail().ToList();
            var attribute = result.Head();
            result = result.Tail().ToList();

            if (environment.IniFile == null)
            {
                environment.Out.WriteLine(Strings.Warning_NoFileLoaded);
                return result;
            }

            if (string.IsNullOrEmpty(sectionName))
            {
                environment.Out.WriteLine(Strings.Warning_NoSectionNameGiven);
                return result;
            }

            if (string.IsNullOrEmpty(attribute))
            {
                environment.Out.WriteLine(Strings.Warning_NoAttributeGiven);
                return result;
            }


            var section = environment.IniFile.FindSection(sectionName);
            if (section == null)
            {
                environment.Out.WriteLine(Strings.Error_SectionNotFound);
                return result;
            }

            environment.IniFile.RemoveEntry(sectionName, attribute);

            return result;
        }
    }
}