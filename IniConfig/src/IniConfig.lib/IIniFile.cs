using System.Collections.Generic;

namespace IniConfig.lib
{
    public interface IIniFile
    {
        string FileName { get; }
        List<IniSection> Sections { get; }
    }
}