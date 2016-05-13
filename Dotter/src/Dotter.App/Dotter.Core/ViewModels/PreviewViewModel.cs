using System;
using Dotter.App;
using Prism.Events;
using Prism.Mvvm;

namespace Dotter.Core.ViewModels
{
    public class PreviewViewModel : BindableBase
    {
        private readonly DotCaller _dotCaller = new DotCaller();
        private Uri _preview;

        public PreviewViewModel(IEventAggregator eventAggregator)
        {
            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(text => OnInputUpdated(text));
        }

        public Uri Preview
        {
            get { return _preview; }
            set { _preview = value; OnPropertyChanged(); }
        }

        private void OnInputUpdated(string text)
        {
            var previewFile = _dotCaller.Run(text);
            if (string.IsNullOrEmpty(previewFile)) return;

            Preview = null;
            Preview = new Uri(previewFile, UriKind.Absolute);
        }
    }
}