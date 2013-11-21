using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Contracts;
using IniConfig.Editor.lib.Helpers;
using IniConfig.Editor.lib.Models;
using IniConfig.Editor.lib.Resources;
using Microsoft.Practices.Prism.Commands;
using Microsoft.Practices.Prism.Events;
using Microsoft.Practices.Unity;

namespace IniConfig.Editor.lib.ViewModels
{
    public class MenuBarViewModel : IViewModel
    {
        readonly AppConfiguration _appConfiguration;
        readonly EventAggregator _eventAggregator;

        [Dependency]
        public IProvideFileSource FileSourceProvider { get; set; }

        public MenuBarViewModel(AppConfiguration appConfiguration, EventAggregator eventAggregator)
        {
            _appConfiguration = appConfiguration;
            _eventAggregator = eventAggregator;

            RecentFiles = new ObservableCollection<RecentFile>();
            _appConfiguration.RecentFileRemoved += OnRecentFileRemoved;
            _appConfiguration.RecentFileAdded += OnRecentFileAdded;

            FillRecentFiles();

            NewCommand = new DelegateCommand(OnNew, CanNew);
            LoadCommand = new DelegateCommand(OnLoad);
            SaveCommand = new DelegateCommand(OnSave, CanSave);
            SaveAsCommand = new DelegateCommand(OnSaveAs, CanSaveAs);
            QuitCommand = new DelegateCommand(OnExit);
        }

        public Document Document { get; private set; }
        public ObservableCollection<RecentFile> RecentFiles { get; private set; }

        RecentFile _currentRecentFile;
        public RecentFile CurrentRecentFile
        {
            get { return _currentRecentFile; }
            set
            {
                _currentRecentFile = value;
                OpenConfigurationFile(_currentRecentFile.FilePath);
            }
        }

        #region Commands

        public ICommand NewCommand { get; private set; }

        void OnNew()
        {
        }

        bool CanNew()
        {
            return true;
        }

        public ICommand LoadCommand { get; private set; }

        void OnLoad()
        {
            var fileFilter = string.Format("{0} (*.ini)|*.ini|{1} (*.*)|*.*",
                                           Strings.MenuBarViewModel_ConfigurationFiles,
                                           Strings.MenuBarViewModel_AllFiles);
            var obtainFileSettings = new ObtainFileSettings
                {
                    LastLocation = _appConfiguration.LastOpenLocation,
                    FileFilterIndex = _appConfiguration.LastFilterIndex,
                    FileFilter = fileFilter,
                    DialogTitle = Strings.MenuBarViewModel_SelectConfigurationFile,
                };

            var fileName = FileSourceProvider.ObtainFileName(obtainFileSettings);
            if (string.IsNullOrEmpty(fileName)) return;

            _appConfiguration.LastOpenLocation = obtainFileSettings.LastLocation;
            _appConfiguration.LastFilterIndex = obtainFileSettings.FileFilterIndex;

            OpenConfigurationFile(fileName);
        }

        public ICommand SaveCommand { get; private set; }

        void OnSave()
        {

        }

        bool CanSave()
        {
            return Document!=null && Document.HasChanged;
        }
        
        public ICommand SaveAsCommand { get; private set; }

        void OnSaveAs()
        {
        }

        bool CanSaveAs()
        {
            return Document != null;
        }

        public ICommand QuitCommand { get; private set; }

        void OnExit()
        {
            Application.Current.Shutdown();
        }

    #endregion

        void OpenConfigurationFile(string fileName)
        {
            var document = Document.CreateDocument(fileName);
            if (document == null)
            {
                _appConfiguration.RemoveRecentFile(fileName);
                _eventAggregator.GetEvent<ShowStatusMessageEvent>()
                                .Publish(string.Format(Strings.MenuBarViewModel_CouldNotLoadFile, fileName));
                return;
            }
            Document = document;
            _appConfiguration.UpdateRecentFiles(fileName);

            //CurrentInputFile = fileName;
            _eventAggregator.GetEvent<ShowStatusMessageEvent>()
                            .Publish(string.Format(Strings.MenuBarViewModel_FileLoaded, fileName));
            _eventAggregator.GetEvent<DocumentChangedEventEvent>().Publish(Document);
        }
        
        void FillRecentFiles()
        {
            foreach (var recentFile in _appConfiguration.RecentFiles.Reverse())
            {
                RecentFiles.Add(recentFile);
            }
        }

        void OnRecentFileAdded(object sender, RecentFileEvent e)
        {
            if (Application.Current == null)
                RecentFiles.Insert(0, e.RecentFile); // For testing purposes
            else
                Application.Current.Dispatcher.Invoke(DispatcherPriority.Normal, new Action(() => RecentFiles.Insert(0, e.RecentFile)));
        }

        void OnRecentFileRemoved(object sender, RecentFileEvent e)
        {
            if (Application.Current == null)
                RecentFiles.Remove(e.RecentFile); // For testing purposes
            else
                Application.Current.Dispatcher.Invoke(DispatcherPriority.Normal, new Action(() => RecentFiles.Remove(e.RecentFile)));
        }
    }
}