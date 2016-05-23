using System.Collections.ObjectModel;
using Prism.Events;

namespace Dotter.Core.ViewModels
{
    public class WizardNodesPageViewModel
    {
        private readonly IEventAggregator _eventAggregator;
        public ObservableCollection<string> Nodes { get; set; }

        public WizardNodesPageViewModel(IEventAggregator eventAggregator)
        {
            Nodes = new ObservableCollection<string>();

            eventAggregator.GetEvent<NewNodeInConnectAdded>().Subscribe(AddNodeIfMissing);
            _eventAggregator = eventAggregator;
        }

        private void AddNodeIfMissing(string node)
        {
            if(!Nodes.Contains(node)) Nodes.Add(node);
        }
    }
}