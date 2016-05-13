using Microsoft.Win32;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace Dotter.Core.ViewModels
{
    public class MenuViewModel : BindableBase
    {
        private readonly IEventAggregator _eventAggregator;
        private bool _inputEmpty;
        private bool _inputDifferent;

        public MenuViewModel(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;
            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(OnInputUpdated);
            eventAggregator.GetEvent<FileSavedEvent>().Subscribe(OnInputLoadedOrSaved);
            eventAggregator.GetEvent<FileLoadedEvent>().Subscribe(OnInputLoadedOrSaved);
            OnInputUpdated(string.Empty);
        }

        #region File New
        public DelegateCommand FileNewCommand
        {
            get { return new DelegateCommand(DoFileNew, CanFileNew).ObservesProperty(()=>this.InputEmpty); }
        }


        private void DoFileNew()
        {
            _eventAggregator.GetEvent<ClearTextInputEvent>().Publish(0);
        }
        private bool CanFileNew()
        {
            return !InputEmpty;
        }

        #endregion

        #region File Open
        public DelegateCommand FileOpenCommand { get { return new DelegateCommand(DoFileOpen); } }

        private void DoFileOpen()
        {
            var openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "DOT files (*.dot)|*.dot|All files (*.*)|*.*";
            if (openFileDialog.ShowDialog() != true) return;

            _eventAggregator.GetEvent<LoadFileEvent>().Publish(openFileDialog.FileName);
        }
        #endregion

        #region File Save
        public DelegateCommand FileSaveCommand
        {
            get { return new DelegateCommand(DoFileSave, CanFileSave).ObservesProperty(() => this.InputDifferent); }
        }

        private void DoFileSave()
        {
            /*
                        var saveFileDialog = new SaveFileDialog();
                        saveFileDialog.Filter = "*.dot";
                        if (saveFileDialog.ShowDialog() != true) return;

                        _eventAggregator.GetEvent<SaveFileEvent>().Publish(saveFileDialog.FileName);
            */
            _eventAggregator.GetEvent<SaveFileEvent>().Publish(0);
        }
        private bool CanFileSave()
        {
            return InputDifferent;
        }
        #endregion

        private string FormerInput { get; set; }

        bool InputEmpty
        {
            get { return _inputEmpty; }
            set { _inputEmpty = value; OnPropertyChanged(); }
        }

        bool InputDifferent
        {
            get { return _inputDifferent; }
            set { _inputDifferent = value; OnPropertyChanged(); }
        }

        private void OnInputUpdated(string text)
        {
            InputEmpty = string.IsNullOrEmpty(text);
            InputDifferent = FormerInput != text;
        }

        private void OnInputLoadedOrSaved(string text)
        {
            FormerInput = text;
            InputDifferent = false;
        }
    }
}