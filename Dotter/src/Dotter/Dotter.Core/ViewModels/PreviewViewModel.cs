using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;
using Dotter.App;
using Prism.Events;
using Prism.Mvvm;

namespace Dotter.Core.ViewModels
{
    public class PreviewViewModel : BindableBase
    {
        readonly IEventAggregator _eventAggregator;
        private readonly DotCaller _dotCaller = new DotCaller();
        private Uri _preview;

        public PreviewViewModel(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;
            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(OnInputUpdated);
            eventAggregator.GetEvent<CopyPreviewEvent>().Subscribe(_ => OnCopyPreview());
        }

        BitmapImage _previewImage;
        public BitmapImage PreviewImage
        {
            get { return _previewImage; }
            private set
            {
                _previewImage = value;
                OnPropertyChanged();
            }
        }

        public Uri Preview
        {
            get { return _preview; }
            set { 
                _preview = value; 
                OnPropertyChanged(); 

                var image = new BitmapImage();
                image.BeginInit();
                image.CacheOption = BitmapCacheOption.OnLoad;
                image.UriSource = _preview;
                image.EndInit();
                PreviewImage = image;
            }
        }

        string _oldPreviewFile;

        private void OnInputUpdated(string text)
        {
            var previewFile = _dotCaller.Run(text);
            if (string.IsNullOrEmpty(previewFile))
            {
                _eventAggregator.GetEvent<StatusbarMessageEvent>().Publish("Could not process input");
                return;
            }

            Preview = new Uri(previewFile, UriKind.Absolute);
            if (!string.IsNullOrEmpty(_oldPreviewFile))
            {
                try
                {
                    File.Delete(_oldPreviewFile);
                }
                catch (Exception)
                {
                }
            }
            _oldPreviewFile = previewFile;
            _eventAggregator.GetEvent<PreviewUpdatedEvent>().Publish(previewFile);
            _eventAggregator.GetEvent<StatusbarMessageEvent>().Publish("Preview updated");
        }

        void OnCopyPreview()
        {
            Clipboard.SetImage(PreviewImage);
        }
    }
}