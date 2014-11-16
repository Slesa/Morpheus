using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe6))]
    internal class When_calculating_square_difference_of_10
    {
        Establish context = () => _aufgabe = new Aufgabe6();

        Because of = () => _result = _aufgabe.Calculate(10);

        It should_be_right = () => _result.ShouldEqual(2640);

        static Loesung6 _aufgabe;
        static int _result;
    }
}