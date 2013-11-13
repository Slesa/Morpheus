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

        public static IniSection CreateSection(IniLine nameLine, List<IniLine> remarkLines)
        {
            return new IniSection {_nameLine = nameLine, _remarkLines = remarkLines};
        }

        IniLine _nameLine;
        public string Name
        {
            get { return _nameLine.Section; }
            set
            {
                if(_nameLine==null) _nameLine = new IniLine();
                _nameLine.Section = value;
            }
        }


        /// <summary>
        /// All lines of this section
        /// </summary>
        public IEnumerable<IniLine> Lines
        {
            get
            {
                if (_remarkLines != null)
                {
                    foreach (var remarkLine in _remarkLines) yield return remarkLine;
                }
                if (_nameLine != null)
                {
                    yield return _nameLine;
                }
                if (Entries != null)
                {
                    foreach (var entryLine in Entries.SelectMany(entry => entry.Lines))
                    {
                        yield return entryLine;
                    }
                }
            }
        }
        List<IniLine> LineList
        {
            get { return (List<IniLine>)Lines; }
        }


        List<IniLine> _remarkLines;
        public IEnumerable<string> Remarks
        {
            get
            {
                if(_remarkLines==null) _remarkLines = new List<IniLine>();
                return _remarkLines.Select(x=>x.Comment);
            }
        }
        List<IniLine> RemarksList
        {
            get { return _remarkLines ?? (_remarkLines = new List<IniLine>()); }
        }

        public IniSection AddRemark(string remark)
        {
            RemarksList.Add(new IniLine {Comment = remark});
            return this;
        }

        public IniSection AddRemarks(IEnumerable<string> remarks)
        {
            foreach(var remark in remarks) AddRemark(remark);
            return this;
        }

        public IniSection SetRemarks(List<IniLine> remarkLines)
        {
            _remarkLines = remarkLines;
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

        public IniSection AddEntry(string attribute, string value)
        {
            var element = FindEntry(attribute);
            if (element != null)
                element.Value = value;
            else
                EntryList.Add(new IniEntry(new IniLine{Entry=attribute, Value=value}));
            return this;
        }

        public void AddEntry(IniEntry entry)
        {
            EntryList.Add(entry);
        }

        public void RemoveEntry(string attribute)
        {
            var entry = FindEntry(attribute);
            if (entry == null) return;
            EntryList.Remove(entry);
        }
    }
}