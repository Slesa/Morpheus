using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Helpers;
using Microsoft.Practices.Prism.Commands;

namespace IniConfig.Editor.lib.ViewModels
{
    public class MenuBarViewModel : IViewModel
    {
        readonly AppConfiguration _appConfiguration;

        public MenuBarViewModel(AppConfiguration appConfiguration)
        {
            _appConfiguration = appConfiguration;

            RecentFiles = new ObservableCollection<RecentFile>();
            _appConfiguration.RecentFileRemoved += OnRecentFileRemoved;
            _appConfiguration.RecentFileAdded += OnRecentFileAdded;

            FillRecentFiles();

            LoadCommand = new DelegateCommand(OnLoad);
            SaveCommand = new DelegateCommand(OnSave);
            SaveAsCommand = new DelegateCommand(OnSaveAs);
            ExitCommand = new DelegateCommand(OnExit);
        }

        public ObservableCollection<RecentFile> RecentFiles { get; private set; }

    #region Commands

        public ICommand LoadCommand { get; private set; }

        void OnLoad()
        {

        }

        public ICommand SaveCommand { get; private set; }

        void OnSave()
        {

        }
        
        public ICommand SaveAsCommand { get; private set; }

        void OnSaveAs()
        {

        }

        public ICommand ExitCommand { get; private set; }

        void OnExit()
        {
            Application.Current.Shutdown();
        }

    #endregion
        
        void FillRecentFiles()
        {
            foreach (var recentFile in _appConfiguration.RecentFiles.Reverse())
            {
                RecentFiles.Add(recentFile);
            }
        }

        void OnRecentFileAdded(object sender, RecentFileEvent e)
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Normal,
                                                  new Action(() => RecentFiles.Insert(0, e.RecentFile)));
        }

        void OnRecentFileRemoved(object sender, RecentFileEvent e)
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Normal,
                                                  new Action(() => RecentFiles.Remove(e.RecentFile)));
        }
    }
}