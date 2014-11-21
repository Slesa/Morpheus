using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe8))]
    public class When_finding_4_adjacent_digits
    {
        Establish context = () => _aufgabe = new Aufgabe8();

        Because of = () => _result = _aufgabe.Calculate(4);

        It should_solve = () => _result.ShouldEqual(5832.0);

        static Loesung8 _aufgabe;
        static double _result;
    }
}