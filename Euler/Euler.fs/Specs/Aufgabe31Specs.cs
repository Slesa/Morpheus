using Aufgaben;
using Machine.Specifications;
using Microsoft.FSharp.Collections;

namespace Specs
{
    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(1, new FSharpList<int>(0, null)));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins);

        It should_have_2_ways = () => _result.ShouldEqual(2);

        static Loesung31 _aufgabe;
        static int _result;
        static FSharpList<int> _coins;
    }
}