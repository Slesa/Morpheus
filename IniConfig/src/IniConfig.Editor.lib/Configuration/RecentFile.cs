using System.Diagnostics;

namespace IniConfig.Editor.lib.Configuration
{
    [DebuggerDisplay("{Name}, {FilePath}")]
    public class RecentFile
    {
        public string Name { get; set; }
        public string FilePath { get; set; }
    }
}