using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace IniConfig.lib
{
    public class IniFile
    {
        string _fileName;

        public static IniFile LoadFrom(string fileName)
        {
            var iniFile = new IniFile();
            iniFile.Load(fileName);
            return iniFile;
        }

        List<IniLine> _lines;
        public List<IniLine> Lines
        {
            get { return _lines ?? (_lines = new List<IniLine>()); }
        }
            
        List<IniSection> _sections;
        public List<IniSection> Sections
        {
            get { return _sections ?? (_sections = new List<IniSection>()); }
        }


        void Load(string fileName)
        {
            _fileName = fileName;
            var buffer = File.ReadAllText(_fileName, Encoding.UTF8);
            LoadFromText(buffer);
        }

        internal void LoadFromText(string buffer)
        {
            IniSection currentSection = null;

            foreach (var line in buffer.Split('\n'))
            {
                var iniLine = new IniLine(line);
                Lines.Add(iniLine);

                if (iniLine.IsComment)
                {
                    //currentSection.Remarks.Add(line);
                    continue;
                }
                if (iniLine.IsSection)
                {
                    var sectionName = iniLine.Section;
                    if (Sections.Any(x=>x.Name.Equals(sectionName))) continue;
                    currentSection = new IniSection() {Name = sectionName};
                    Sections.Add(currentSection);
                }
            }
        }
    }
}

