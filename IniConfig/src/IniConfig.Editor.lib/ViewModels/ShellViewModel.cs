using System.Linq;
using System.Reflection;
using System.Windows;
using System.Windows.Shell;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Contracts;
using Microsoft.Practices.Unity;

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

        [Dependency]
        public MenuBarViewModel MenuBar { get; set; }

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