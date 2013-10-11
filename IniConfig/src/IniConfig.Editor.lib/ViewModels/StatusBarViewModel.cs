using IniConfig.Editor.lib.Contracts;
using Microsoft.Practices.Prism.Events;

namespace IniConfig.Editor.lib.ViewModels
{
    public class StatusBarViewModel : IViewModel
    {
        public StatusBarViewModel(IEventAggregator eventAggregator)
        {
            eventAggregator.GetEvent<ShowStatusMessageEvent>().Subscribe(x => Message = x);
        }

        public string Message { get; set; }
    }

}