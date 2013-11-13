using System.Collections.Generic;

namespace IniConfig.lib
{
    public interface IIniFile
    {
        string FileName { get; }
        IEnumerable<IniSection> Sections { get; }

        IniSection FindSection(string name);
        IniSection AddSection(string name, IEnumerable<string> remarks = null);

        IniEntry FindEntry(string sectionName, string entryName);
        IniEntry AddEntry(string sectionName, string attribute, string value);
        void RemoveEntry(string sectionName, string entryName);
    }
}