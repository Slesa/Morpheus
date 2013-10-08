using System.Collections.Generic;
using System.IO;
using System.Text;

namespace IniConfig.lib
{
    public class IniFile
    {
        public static IniFile LoadFrom(string fileName)
        {
            var iniFile = new IniFile();
            iniFile.Load(fileName);
            return iniFile;
        }

        List<IniSection> _sections;
        public List<IniSection> Sections
        {
            get { return _sections ?? (_sections = new List<IniSection>()); }
        }


        void Load(string fileName)
        {
            var buffer = File.ReadAllText(fileName, Encoding.UTF8);
            LoadFromText(buffer);
        }

        internal void LoadFromText(string buffer)
        {
            var currentSection = new IniSection();

            foreach (var line in buffer.Split('\n'))
            {
                var iniLine = new IniLine(line);
                if (iniLine.IsComment)
                {
                    currentSection.Remarks.Add(line);
                    continue;
                }
                if (iniLine.IsSection)
                {
                    
                }
            }
        }
    }
}

