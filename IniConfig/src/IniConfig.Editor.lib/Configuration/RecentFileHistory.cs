using System;
using System.Collections.Generic;
using System.IO;
using System.Xml.Linq;

namespace IniConfig.Editor.lib.Configuration
{
    public class RecentFileHistory : IProvideRecentFiles
    {
        const string RecentHistoryFile = "IniConfig.Editor.recent";
        const string RecentFilesTag = "RecentFiles";
        const string RecentFileTag = "RecentFile";
        const string NameTag = "Name";
        const string FilePathTag = "File";

        static string FileName
        {
            get
            {
                var path = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
                path = CreatePathIfNeeded(path, "Slesa Solutions");
                path = CreatePathIfNeeded(path, "IniConfig");
                return Path.Combine(path, RecentHistoryFile);
            }
        }

        static string CreatePathIfNeeded(string path, string newFolder)
        {
            path = Path.Combine(path, newFolder);
            var directoryInfo = new DirectoryInfo(path);
            if (!directoryInfo.Exists)
                directoryInfo.Create();
            return path;
        }

        public List<RecentFile> LoadHistory()
        {
            var recentFiles = new List<RecentFile>();
            var fn = FileName;
            if (File.Exists(fn))
            {
                var xDocument = XDocument.Load(fn);
                foreach (var node in xDocument.Descendants(RecentFileTag))
                {
                    var nameAttr = node.Attribute(NameTag);
                    if (nameAttr == null) continue;

                    var filePathAttr = node.Attribute(FilePathTag);
                    if (filePathAttr == null) continue;

                    recentFiles.Add(new RecentFile
                        {
                            Name = nameAttr.Value,
                            FilePath = filePathAttr.Value,
                        });
                }
            }
            return recentFiles;
        }

        public void StoreHistory(IEnumerable<RecentFile> recentFiles)
        {
            var xDocument = new XDocument(new XDeclaration("1.0", "UTF-8", "yes"));
            var root = new XElement(RecentFilesTag);
            xDocument.Add(root);
            foreach (var recentFile in recentFiles)
            {
                var node = new XElement(RecentFileTag);
                node.Add(new XAttribute(NameTag, recentFile.Name));
                node.Add(new XAttribute(FilePathTag, recentFile.FilePath));
                root.Add(node);
            }
            xDocument.Save(FileName);
        }
    }
}
