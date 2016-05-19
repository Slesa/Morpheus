using System.Collections.ObjectModel;
using Dotter.Grammar;
using Prism.Events;

namespace Dotter.Core.ViewModels
{
    public class GrammarViewModel : IHandleParserErrors
    {
        readonly DotterParser _parser;

        public GrammarViewModel(IEventAggregator eventAggregator)
        {
            ParserErrors = new ObservableCollection<ErrorDescription>();
            _parser = new DotterParser(this);

            eventAggregator.GetEvent<TextInputUpdatedEvent>().Subscribe(OnTextUpdated);
        }

        void OnTextUpdated(string text)
        {
            ParserErrors.Clear();
            _parser.ParseValid(text);
        }

        public ObservableCollection<ErrorDescription> ParserErrors { get; private set; }

        public void HandleError(ErrorDescription error)
        {
            ParserErrors.Add(error);
        }
    }
}