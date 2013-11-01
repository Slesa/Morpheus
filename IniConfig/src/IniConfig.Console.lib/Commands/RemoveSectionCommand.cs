using System.Collections.Generic;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;

namespace IniConfig.Console.lib.Commands
{
    public class RemoveSectionCommand : IMenuCommand
    {
        public RemoveSectionCommand()
        {
            Shortcut = "rs";
            Description = Strings.RemoveSectionCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            return null;
        }
    }
}