using System.Collections.Generic;
using System.Linq;

namespace IniConfig.lib
{
    public class IniSection
    {
        public static IniSection CreateSection(string name)
        {
            return new IniSection {Name = name};
        }

        public string Name { get; set; }

        List<string> _remarks;
        public List<string> Remarks
        {
            get { return _remarks ?? (_remarks = new List<string>()); }
        }

        public IniSection AddRemark(string remark)
        {
            Remarks.Add(remark);
            return this;
        }

        public IniSection AddRemarks(IEnumerable<string> remarks)
        {
            Remarks.AddRange(remarks);
            return this;
        }

        List<IniEntry> _entries;
        public IEnumerable<IniEntry> Entries
        {
            get { return _entries ?? (_entries = new List<IniEntry>()); }
        }
        List<IniEntry> EntryList
        {
            get { return (List<IniEntry>)Entries; }
        }

        public IniEntry FindEntry(string name)
        {
            return Entries.FirstOrDefault(s => s.Attribute.ToLower().Equals(name.ToLower()));
        }

        public IniSection AddElement(string attribute, string value)
        {
            var element = FindEntry(attribute);
            if (element != null)
                element.Value = value;
            else
                EntryList.Add(new IniEntry(new IniLine{Entry=attribute, Value=value}));
            return this;
        }

        public void AddElementLine(IniLine iniLine)
        {
            EntryList.Add(new IniEntry(iniLine));
        }
    }
}