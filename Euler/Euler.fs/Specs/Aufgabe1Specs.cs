using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe1))]
    internal class When_solving_task1_using_limit_10
    {
        Establish context = () => _aufgabe1 = new Aufgabe1();

        Because of = () => _result = _aufgabe1.Calculate(10);

        It should_calculate = () => _result.ShouldEqual(23);

        static Loesung1 _aufgabe1;
        static int _result;
    }

    [Subject(typeof(Aufgabe1))]
    internal class When_solving_task1_using_limit_20
    {
        Establish context = () => _aufgabe1 = new Aufgabe1();

        Because of = () => _result = _aufgabe1.Calculate(20);

        // Are multiples of 3 and 5 counted twice or not?
        It should_calculate = () => _result.ShouldEqual(78);
        //It should_calculate = () => _result.ShouldEqual(93);

        static Loesung1 _aufgabe1;
        static int _result;
    }

    [Subject(typeof(Aufgabe1))]
    internal class When_solving_task1_using_limit_30
    {
        Establish context = () => _aufgabe1 = new Aufgabe1();

        Because of = () => _result = _aufgabe1.Calculate(30);

        // Are multiples of 3 and 5 counted twice or not?
        It should_calculate = () => _result.ShouldEqual(195);

        static Loesung1 _aufgabe1;
        static int _result;
    }
}