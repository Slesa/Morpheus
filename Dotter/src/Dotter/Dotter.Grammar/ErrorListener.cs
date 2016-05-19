using System.Collections.Generic;
using Antlr4.Runtime;

namespace Dotter.Grammar
{
    public class ErrorDescription
    {
        public int Line { get; private set; }
        public string Msg { get; private set; }

        public ErrorDescription(int line, string msg)
        {
            Line = line;
            Msg = msg;
        }
    }

    public class ErrorListener : BaseErrorListener
    {
        readonly List<ErrorDescription> _errorDescriptions = new List<ErrorDescription>();

        public override void SyntaxError(IRecognizer recognizer, IToken offendingSymbol, int line, int charPositionInLine, string msg,
            RecognitionException e)
        {
            base.SyntaxError(recognizer, offendingSymbol, line, charPositionInLine, msg, e);
            _errorDescriptions.Add(new ErrorDescription(line, msg));
        }

        public List<ErrorDescription> ErrorDescriptions  { get { return _errorDescriptions; } }
    }
}