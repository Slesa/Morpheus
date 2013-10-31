using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class ListEntriesCommand : IMenuCommand
    {
        public ListEntriesCommand()
        {
            Shortcut = "le";
            Description = Strings.ListEntriesCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var sectionName = nextToken.Head();
            var result = nextToken.Tail().ToList();

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

            var section = environment.IniFile.FindSection(sectionName);
            if (section==null)
            {
                environment.Out.WriteLine(Strings.Error_SectionNotFound);
                return result;
            }

            foreach (var entry in section.Entries)
            {
                //foreach (var remark in entry.Remarks)
                //    environment.Out.WriteLine(string.Format("// {0}", remark));
                environment.Out.WriteLine(string.Format("{0} = {1}", entry.Attribute, entry.Value));
            }
            return result;
        }
    }
}