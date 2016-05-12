using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Prism.Commands;

namespace Dotter.App
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private string _input;
        private Uri _preview;
        private DotCaller _dotCaller = new DotCaller();
        private bool _hasChanged;

        public DelegateCommand FileNewCommand
        {
            get { return new DelegateCommand(DoFileNew, CanFileNew); }
        }


        private void DoFileNew()
        {
            Input = string.Empty;
            HasChanged = false;
        }
        private bool CanFileNew()
        {
            return !HasChanged;
        }


        public DelegateCommand FileOpenCommand { get { return new DelegateCommand(DoFileOpen); } }

        private void DoFileOpen()
        {
        }

        public DelegateCommand FileSaveCommand
        {
            get { return new DelegateCommand(DoFileSave, CanFileSave); }
        }

        private void DoFileSave()
        {
            
        }
        private bool CanFileSave()
        {
            return HasChanged;
        }

        public bool HasChanged
        {
            get { return _hasChanged; }
            set { _hasChanged = value; OnPropertyChanged(); UpdateCommands(); }
        }

        public string Input
        {
            get { return _input; }
            set
            {
                _input = value;
                OnPropertyChanged();
                HasChanged = true;
                UpdatePreview();
            }
        }


        public Uri Preview
        {
            get { return _preview; }
            set { _preview = value; OnPropertyChanged(); }
        }

        private void UpdatePreview()
        {
            var previewFile = _dotCaller.Run(Input);
            if (string.IsNullOrEmpty(previewFile)) return;

            Preview = new Uri(previewFile, UriKind.Absolute);
        }
        private void UpdateCommands()
        {
            FileNewCommand.RaiseCanExecuteChanged();
            FileSaveCommand.RaiseCanExecuteChanged();
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}