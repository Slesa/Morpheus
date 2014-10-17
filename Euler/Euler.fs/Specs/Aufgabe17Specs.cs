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

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_99
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(99);

        It should_calculate = () => _result.ShouldEqual(47+70 + 9*36);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_101
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(101);

        // 1-9 = 36 * 9
        // 10-90 = 47
        // 11-19 = 70  = 441
        It should_calculate = () => _result.ShouldEqual(441 + (3+7) + (3+7+3+3)); // one hundred + one hundred and one

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_201
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(201);

        It should_calculate = () => _result.ShouldEqual(441*2 + 2*(3+7) + (3+7+3+3) + 99*(3+7+3)); // one hundred + two hundred + two hundred and one + one hundred and * 99

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    public class When_solving_task17_with_limit_999
    {
        Establish context = () => _aufgabe = new Aufgabe17();

        Because of = () => _result = _aufgabe.Calculate(999);

        It should_calculate = () => _result.ShouldEqual((47+70 +9*36)*9 + (36+7+3));

        static Loesung17 _aufgabe;
        static int _result;
    }
}