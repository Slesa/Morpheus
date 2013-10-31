using System.Collections.Generic;

namespace IniConfig.lib
{
    public interface IIniFile
    {
        string FileName { get; }
        IEnumerable<IniSection> Sections { get; }
        IniSection AddSection(string name, IEnumerable<string> remarks = null);
        IniSection FindSection(string name);
    }
}