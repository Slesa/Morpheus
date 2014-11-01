using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe4))]
    internal class When_checking_empty_string_for_palindrom
    {
        Establish context = () => _aufgabe = new Aufgabe4();

        Because of = () => _result = _aufgabe.IsPalindrom("");

        It should_return_true = () => _result.ShouldBeTrue();

        static Loesung4 _aufgabe;
        static bool _result;
    }

    [Subject(typeof(Aufgabe4))]
    internal class When_checking_non_palindrom
    {
        Establish context = () => _aufgabe = new Aufgabe4();

        Because of = () => _result = _aufgabe.IsPalindrom("abc");

        It should_return_false = () => _result.ShouldBeFalse();

        static Loesung4 _aufgabe;
        static bool _result;
    }

    [Subject(typeof(Aufgabe4))]
    internal class When_checking_equal_length_for_palindrom
    {
        Establish context = () => _aufgabe = new Aufgabe4();

        Because of = () => _result = _aufgabe.IsPalindrom("abba");

        It should_return_true = () => _result.ShouldBeTrue();

        static Loesung4 _aufgabe;
        static bool _result;
    }

    [Subject(typeof(Aufgabe4))]
    internal class When_checking_unequal_length_for_palindrom
    {
        Establish context = () => _aufgabe = new Aufgabe4();

        Because of = () => _result = _aufgabe.IsPalindrom("abxba");

        It should_return_true = () => _result.ShouldBeTrue();

        static Loesung4 _aufgabe;
        static bool _result;
    }

    [Subject(typeof(Aufgabe4))]
    internal class When_calculationg_max_palindrom_for_100
    {
        Establish context = () => _aufgabe = new Aufgabe4();

        Because of = () => _result = _aufgabe.FindMaximum(100, 10);

        It should_return_true = () => _result.ShouldEqual("9009");

        static Loesung4 _aufgabe;
        static string _result;
    }
}