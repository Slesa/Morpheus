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

        void Load(string fileName)
        {
            var buffer = File.ReadAllText(fileName, Encoding.UTF8);
            var remarks = new List<string>();

            IniSection currentSection = null;
            foreach (var line in buffer.Split('\n'))
            {
            }
        }
    }
}

