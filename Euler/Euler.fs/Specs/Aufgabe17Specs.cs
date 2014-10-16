using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_10
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(10);

        It should_calculate = () => _result.ShouldEqual(3);

        static Loesung17 _aufgabe;
        static int _result;
    }
}