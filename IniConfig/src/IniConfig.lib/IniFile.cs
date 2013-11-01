using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace IniConfig.lib
{
    /// <summary>
    /// Manage configuration files with INI syntax.
    /// </summary>
    public class IniFile : IIniFile
    {
        /// <summary>
        /// Creates an instance of an IniFile by loading its content from the given file.
        /// </summary>
        /// <param name="fileName">The file with the configuration content</param>
        /// <returns></returns>
        public static IniFile LoadFrom(string fileName)
        {
            var iniFile = new IniFile();
            iniFile.Load(fileName);
            return iniFile;
        }


        /// <summary>
        /// The filename of this configuration file, if already loaded
        /// </summary>
        public string FileName { get; private set; }


        List<IniLine> _lines;
        /// <summary>
        /// All lines of the configuration file, not separated in sections
        /// </summary>
        public IEnumerable<IniLine> Lines
        {
            get { return _lines ?? (_lines = new List<IniLine>()); }
        }
        /// <summary>
        /// All lines of the configuration file as a list in order to add or remove something
        /// </summary>
        List<IniLine> LineList
        {
            get { return (List<IniLine>)Lines; }
        }
        
    
        List<IniSection> _sections;
        /// <summary>
        /// All sections of the configuration file
        /// </summary>
        public IEnumerable<IniSection> Sections
        {
            get { return _sections ?? (_sections = new List<IniSection>()); }
        }
        /// <summary>
        /// All sections of the configuration file as a list on order to add or remove something
        /// </summary>
        List<IniSection> SectionList
        {
            get { return (List<IniSection>) Sections; }
        }

        /// <summary>
        /// Search a section by its name, case independent
        /// </summary>
        /// <param name="name">Name of the section to search for</param>
        /// <returns>null or the found section</returns>
        public IniSection FindSection(string name)
        {
            return Sections.FirstOrDefault(s => s.Name.ToLower().Equals(name.ToLower()));
        }

        /// <summary>
        /// Add a new section with name and a list of comments. If the section already exists, the existing instance is returned
        /// </summary>
        /// <param name="name">The name of the new section</param>
        /// <param name="remarks">The comment of this section</param>
        /// <returns>The new created section or the already existing one</returns>
        public IniSection AddSection(string name, IEnumerable<string> remarks = null)
        {
            var section = FindSection(name);
            if (section != null) return section;

            section = IniSection.CreateSection(name);
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


        /// <summary>
        /// Search an entry of the section sectionName by its name
        /// </summary>
        /// <param name="sectionName">The name of the section of the entry</param>
        /// <param name="entryName">Name of the entry to search for</param>
        /// <returns>null or the found entry</returns>
        public IniEntry FindEntry(string sectionName, string entryName)
        {
            var section = FindSection(sectionName);
            return section == null ? null : section.FindEntry(entryName);
        }

        /// <summary>
        /// Add a new entry to the section sectionName with name entryName and value.
        /// </summary>
        /// <param name="sectionName">Name of the section to add the entry to</param>
        /// <param name="entryName">Name of the entry to add</param>
        /// <param name="value">Value of the new entry</param>
        /// <returns></returns>
        public IniEntry AddEntry(string sectionName, string entryName, string value)
        {
            var section = FindSection(sectionName);
            return section == null ? null : section.AddElement(entryName, value).FindEntry(entryName);
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
                    currentSection.AddElementLine(iniLine);
                }
            }
        }
    }
}

