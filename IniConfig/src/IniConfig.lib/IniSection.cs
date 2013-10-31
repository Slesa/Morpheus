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
                ((List<IniEntry>)Entries).Add(new IniEntry(attribute, value));
            return this;
        }
    }
}