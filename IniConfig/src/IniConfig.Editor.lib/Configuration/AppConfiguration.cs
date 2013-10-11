using System;
using System.Collections.Generic;
using System.Linq;

namespace IniConfig.Editor.lib.Configuration
{
    public class RecentFileEvent : EventArgs
    {
        public RecentFileEvent(RecentFile recentFile)
        {
            RecentFile = recentFile;
        }
        public RecentFile RecentFile { get; private set; }
    }

    public class AppConfiguration
    {
        readonly IProvideSettings _settingsProvider;
        readonly IProvideRecentFiles _recentFilesProvider;

        public AppConfiguration(IProvideSettings settingsProvider, IProvideRecentFiles recentFilesProvider)
        {
            _settingsProvider = settingsProvider;
            _recentFilesProvider = recentFilesProvider;
        }

        public int MaxRecentFiles
        {
            get { return _settingsProvider.MaxRecentFiles; }
            set { _settingsProvider.MaxRecentFiles = value; }
        }

        public string LastOpenLocation
        {
            get { return _settingsProvider.LastOpenLocation; }
            set { _settingsProvider.LastOpenLocation = value; }
        }

        public int LastFilterIndex
        {
            get { return _settingsProvider.LastFilterIndex; }
            set { _settingsProvider.LastFilterIndex = value; }
        }

        List<RecentFile> _recentFiles;
        
        public event EventHandler<RecentFileEvent> RecentFileAdded;
        public event EventHandler<RecentFileEvent> RecentFileRemoved;

        public IEnumerable<RecentFile> RecentFiles
        {
            get
            {
                if (_recentFiles == null)
                {
                    _recentFiles = _recentFilesProvider.LoadHistory();
                    if(MaximumRecentFilesExceeded())
                        _recentFilesProvider.StoreHistory(_recentFiles);
                }
                return _recentFiles;
            }
        }

        public void UpdateRecentFiles(string filePath)
        {
            var element = RecentFiles.FirstOrDefault(x => x.FilePath.Equals(filePath));
            if (element != null)
            {
                if (_recentFiles.Last().FilePath.Equals(filePath)) return;
                OnRecentFileRemoved(element);
                _recentFiles.Remove(element);
            }
            else
            {
                element = new RecentFile() {FilePath = filePath, Name = filePath};
            }
            OnRecentFileAdded(element);
            _recentFiles.Add(element);

            MaximumRecentFilesExceeded();

            _recentFilesProvider.StoreHistory(_recentFiles);
        }

        public void RemoveRecentFile(string fileName)
        {
            var element = RecentFiles.FirstOrDefault(x => x.FilePath == fileName);
            if (element == null) return;

            OnRecentFileRemoved(element);
            _recentFiles.Remove(element);
            _recentFilesProvider.StoreHistory(_recentFiles);
        }


        bool MaximumRecentFilesExceeded()
        {
            var exceeded = false;
            while (_recentFiles.Count > MaxRecentFiles)
            {
                var removed = _recentFiles[0];
                OnRecentFileRemoved(removed);
                _recentFiles.RemoveAt(0);
                exceeded = true;
            }
            return exceeded;
        }

        void OnRecentFileAdded(RecentFile addedRecentFile)
        {
            var handler = RecentFileAdded;
            if(handler!=null) handler(this, new RecentFileEvent(addedRecentFile));
        }

        void OnRecentFileRemoved(RecentFile removedRecentFile)
        {
            var handler = RecentFileRemoved;
            if(handler!=null) handler(this, new RecentFileEvent(removedRecentFile));
        }
    }
}