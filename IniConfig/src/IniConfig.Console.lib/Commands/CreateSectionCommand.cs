using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.Console.lib.Resources;
using IniConfig.lib;

namespace IniConfig.Console.lib.Commands
{
    public class CreateSectionCommand : IMenuCommand
    {
        public CreateSectionCommand()
        {
            Shortcut = "cs";
            Description = Strings.CreateSectionCommand_Description;
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

            environment.IniFile.AddSection(sectionName);

            return result;
        }
    }
}