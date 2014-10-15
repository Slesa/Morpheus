using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe1))]
    internal class When_using_limit_10
    {
        Establish context = () => _aufgabe1 = new Aufgabe1();

        private Because of = () => _result = _aufgabe1.Calculate(10);

        It should_calculate = () => _result.ShouldEqual(14);

        static Loesung1 _aufgabe1;
        static int _result;
    }
}