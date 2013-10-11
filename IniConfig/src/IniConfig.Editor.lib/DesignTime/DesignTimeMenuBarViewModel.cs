using System.Collections.ObjectModel;
using IniConfig.Editor.lib.Configuration;

namespace IniConfig.Editor.lib.DesignTime
{
    public class DesignTimeMenuBarViewModel
    {
        public DesignTimeMenuBarViewModel()
        {
            RecentFiles = new ObservableCollection<RecentFile>()
                {
                    new RecentFile {Name = "Recent 1", FilePath = "RecentFile.One.txt"},
                    new RecentFile {Name = "Recent 2", FilePath = "RecentFile.Two.txt"},
                };

        }
        public ObservableCollection<RecentFile> RecentFiles { get; private set; }
         
    }
}