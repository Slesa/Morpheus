using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_5
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(5);

        It should_calculate = () => _result.ShouldEqual(19);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_10
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(10);

        It should_calculate = () => _result.ShouldEqual(39);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_11
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(11);

        It should_calculate = () => _result.ShouldEqual(45);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_15
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(15);

        It should_calculate = () => _result.ShouldEqual(39+35);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_20
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(20);

        It should_calculate = () => _result.ShouldEqual(39+67+6);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_21
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(21);

        It should_calculate = () => _result.ShouldEqual(39+67+6+3);

        static Loesung17 _aufgabe;
        static int _result;
    }
}