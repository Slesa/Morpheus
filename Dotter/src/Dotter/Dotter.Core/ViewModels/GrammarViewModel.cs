using Dotter.Grammar;
using Prism.Events;

namespace Dotter.Core.ViewModels
{
    public class GrammarViewModel
    {
        readonly DotterParser _parser = new DotterParser();

        public GrammarViewModel(IEventAggregator eventAggregator)
        {
            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(OnTextUpdated);
        }

        void OnTextUpdated(string text)
        {
            _parser.ParseValid(text);
        }
    }
}