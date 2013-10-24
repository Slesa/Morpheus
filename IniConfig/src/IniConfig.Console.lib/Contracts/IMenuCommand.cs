using System.Collections.Generic;

namespace IniConfig.Console.lib.Contracts
{
    public interface IMenuCommand
    {
        string Shortcut { get; }
        string Description { get; }

        List<string> Execute(List<string> nextToken, AppEnvironment environment);
    }
}