using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof (Aufgabe2))]
    internal class When_task2_calculates_fib_1
    {
        Establish context = () => _aufgabe2 = new Aufgabe2();

        Because of = () => _result = _aufgabe2.NextFibonacci(1, 1);

        It should_calculate = () => _result.ShouldEqual(2);

        static Loesung2 _aufgabe2;
        static int _result;
    }

    [Subject(typeof (Aufgabe2))]
    internal class When_task2_calculates_fib_2
    {
        Establish context = () => _aufgabe2 = new Aufgabe2();

        Because of = () => _result = _aufgabe2.NextFibonacci(2, 1);

        It should_calculate = () => _result.ShouldEqual(3);

        static Loesung2 _aufgabe2;
        static int _result;
    }

    [Subject(typeof (Aufgabe2))]
    internal class When_task2_calculates_fib_3
    {
        Establish context = () => _aufgabe2 = new Aufgabe2();

        Because of = () => _result = _aufgabe2.NextFibonacci(3, 2);

        It should_calculate = () => _result.ShouldEqual(5);

        static Loesung2 _aufgabe2;
        static int _result;
    }

    [Subject(typeof (Aufgabe2))]
    internal class When_solving_task2_using_limit_10
    {
        Establish context = () => _aufgabe2 = new Aufgabe2();

        Because of = () => _result = _aufgabe2.Calculate(10);

        It should_calculate = () => _result.ShouldEqual(10);

        static Loesung2 _aufgabe2;
        static int _result;
    }

    [Subject(typeof (Aufgabe2))]
    internal class When_solving_task2_using_limit_50
    {
        Establish context = () => _aufgabe2 = new Aufgabe2();

        Because of = () => _result = _aufgabe2.Calculate(50);

        It should_calculate = () => _result.ShouldEqual(44);

        static Loesung2 _aufgabe2;
        static int _result;
    }
}