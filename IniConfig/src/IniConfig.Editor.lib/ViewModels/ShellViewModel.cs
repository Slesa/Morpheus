using System.Linq;
using System.Reflection;
using System.Windows;
using System.Windows.Shell;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Contracts;
using IniConfig.Editor.lib.Models;
using Microsoft.Practices.Prism.Events;
using Microsoft.Practices.Prism.ViewModel;
using Microsoft.Practices.Unity;

namespace IniConfig.Editor.lib.ViewModels
{
    public class ShellViewModel : NotificationObject, IViewModel
    {
        readonly AppConfiguration _appConfiguration;
        string _windowTitle;

        public ShellViewModel(AppConfiguration appConfiguration, EventAggregator eventAggregator)
        {
            _appConfiguration = appConfiguration;
            FillRecentFiles();

            eventAggregator.GetEvent<DocumentChangedEventEvent>().Subscribe(OnDocumentChanged);
            OnDocumentChanged(null);
        }

        public string WindowTitle
        {
            get { return _windowTitle; }
            set
            {
                _windowTitle = value;
                RaisePropertyChanged(() => WindowTitle);
            }
        }

        void OnDocumentChanged(Document document)
        {
            var title = "INI Editor";
            if (document != null)
                title += " - " + document.FilePath;
            WindowTitle = title;
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