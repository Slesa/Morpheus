using System.Collections.Generic;

namespace IniConfig.Editor.lib.Configuration
{
    public interface IProvideRecentFiles
    {
        List<RecentFile> LoadHistory();
        void StoreHistory(IEnumerable<RecentFile> recentFiles);
    }
}