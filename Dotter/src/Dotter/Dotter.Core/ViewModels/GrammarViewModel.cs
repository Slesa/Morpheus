using System.Collections.ObjectModel;
using Dotter.Grammar;
using Prism.Events;

namespace Dotter.Core.ViewModels
{
    public class GrammarViewModel : IHandleParserErrors
    {
        readonly IEventAggregator _eventAggregator;
        readonly DotterParser _parser;

        public GrammarViewModel(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;
            ParserErrors = new ObservableCollection<ErrorDescription>();
            _parser = new DotterParser(this);

            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(OnTextUpdated);
        }

        void OnTextUpdated(string text)
        {
            ParserErrors.Clear();
            if( _parser.ParseValid(text) )
                _eventAggregator.GetEvent<TextInputValidatedEvent>().Publish(text);
        }

        public ObservableCollection<ErrorDescription> ParserErrors { get; private set; }

        public void HandleError(ErrorDescription error)
        {
            ParserErrors.Add(error);
        }
    }
}