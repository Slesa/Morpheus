using System.Collections.Generic;
using IniConfig.Console.lib.Contracts;
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
            throw new System.NotImplementedException();
        }
    }
}