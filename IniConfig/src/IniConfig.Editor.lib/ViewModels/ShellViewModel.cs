using System.Linq;
using System.Reflection;
using System.Windows;
using System.Windows.Shell;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Contracts;
using IniConfig.Editor.lib.Helpers;

namespace IniConfig.Editor.lib.ViewModels
{
    public class ShellViewModel : IViewModel
    {
        readonly AppConfiguration _appConfiguration;

        public ShellViewModel(AppConfiguration appConfiguration)
        {
            _appConfiguration = appConfiguration;
            FillRecentFiles();
        }

        void FillRecentFiles()
        {
            var jumpList = new JumpList();
            foreach (var recentFile in _appConfiguration.RecentFiles.Reverse())
            {
                var jumpTask = new JumpTask
                {
                    Title = recentFile.Name,
                    Arguments = recentFile.FilePath,
                    CustomCategory = "Recent files",
                    IconResourcePath = Assembly.GetEntryAssembly().CodeBase,
                    ApplicationPath = Assembly.GetEntryAssembly().CodeBase,
                };
                jumpList.JumpItems.Add(jumpTask);
            }
            JumpList.SetJumpList(Application.Current, jumpList);
        }
    }
}