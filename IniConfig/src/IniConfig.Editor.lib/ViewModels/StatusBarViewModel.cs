using IniConfig.Editor.lib.Contracts;
using Microsoft.Practices.Prism.Events;
using Microsoft.Practices.Prism.ViewModel;
using Microsoft.Practices.ServiceLocation;

namespace IniConfig.Editor.lib.ViewModels
{
    public class StatusBarViewModel : NotificationObject, IViewModel
    {
        public StatusBarViewModel(IEventAggregator eventAggregator)
        {
            eventAggregator.GetEvent<ShowStatusMessageEvent>().Subscribe(x => Message = x);
        }

        public StatusBarViewModel()
        {
            var eventAggregator = ServiceLocator.Current.GetInstance<IEventAggregator>();
            eventAggregator.GetEvent<ShowStatusMessageEvent>().Subscribe(x => Message = x);
        }

        string _message;
        public string Message
        {
            get { return _message; }
            set
            {
                _message = value;
                RaisePropertyChanged(() => Message);
            }
        }
    }

}