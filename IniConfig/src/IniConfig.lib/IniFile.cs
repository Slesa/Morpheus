using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace IniConfig.lib
{
    public class IniFile : IIniFile
    {

        public static IniFile LoadFrom(string fileName)
        {
            var iniFile = new IniFile();
            iniFile.Load(fileName);
            return iniFile;
        }

        public string FileName { get; private set; }

        List<IniLine> _lines;
        public IEnumerable<IniLine> Lines
        {
            get { return _lines ?? (_lines = new List<IniLine>()); }
        }
        List<IniLine> LineList
        {
            get { return (List<IniLine>)Lines; }
        }
            
        List<IniSection> _sections;
        public IEnumerable<IniSection> Sections
        {
            get { return _sections ?? (_sections = new List<IniSection>()); }
        }
        List<IniSection> SectionList
        {
            get { return (List<IniSection>) Sections; }
        }

        public IniSection FindSection(string name)
        {
            return Sections.FirstOrDefault(s => s.Name.ToLower().Equals(name.ToLower()));
        }

        public IniSection AddSection(string name, IEnumerable<string> remarks = null)
        {
            var section = IniSection.CreateSection(name);
            SectionList.Add(section);

            if (remarks != null)
            {
                foreach (var remark in remarks)
                {
                    LineList.Add(new IniLine {Comment = remark});
                    section = section.AddRemark(remark);
                }
            }
            LineList.Add(new IniLine{Section = name});
            return section;
        }

        void Load(string fileName)
        {
            FileName = fileName;
            var buffer = File.ReadAllText(FileName, Encoding.UTF8);
            LoadFromText(buffer);
        }

        internal void LoadFromText(string buffer)
        {
            var remarks = new List<string>();
            IniSection currentSection = null;

            foreach (var line in buffer.Split('\n'))
            {
                var iniLine = new IniLine(line);
                LineList.Add(iniLine);
                if (iniLine.IsEmpty)
                {
                    remarks.Clear();
                    continue;
                }
                if (iniLine.IsComment)
                {
                    remarks.Add(iniLine.Comment);
                    continue;
                }
                if (iniLine.IsSection)
                {
                    var sectionName = iniLine.Section;
                    currentSection = FindSection(sectionName);
                    if (currentSection == null)
                    {
                        currentSection = IniSection.CreateSection(sectionName).AddRemarks(remarks);
                        SectionList.Add(currentSection);
                    }
                    remarks.Clear();
                    continue;
                }
                if (currentSection != null)
                {
                    currentSection.AddElement(iniLine.Entry, iniLine.Value);
                }
            }
        }
    }
}

