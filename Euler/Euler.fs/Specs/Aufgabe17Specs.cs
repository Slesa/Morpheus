using System.Collections.Generic;
using System.Linq;
using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_1
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(1);
        It should_calculate = () => _result.ShouldEqual("one");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_10
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(10);
        It should_calculate = () => _result.ShouldEqual("ten");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_19
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(19);
        It should_calculate = () => _result.ShouldEqual("nineteen");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_20
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(20);
        It should_calculate = () => _result.ShouldEqual("twenty");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_21
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(21);
        It should_calculate = () => _result.ShouldEqual("twenty one");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_99
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(99);
        It should_calculate = () => _result.ShouldEqual("ninety nine");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_100
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(100);
        It should_calculate = () => _result.ShouldEqual("one hundred");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_101
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(101);
        It should_calculate = () => _result.ShouldEqual("one hundred and one");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_111
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(111);
        It should_calculate = () => _result.ShouldEqual("one hundred and eleven");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_999
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(999);
        It should_calculate = () => _result.ShouldEqual("nine hundred and ninety nine");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_line_for_1000
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLineFor(1000);
        It should_calculate = () => _result.ShouldEqual("one thousand");

        static Loesung17 _aufgabe;
        static string _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_lines_until_5
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLinesUntil(5);
        It should_calculate_five_lines = () => _result.Count().ShouldEqual(5);
        It should_calculate_line_1 = () => _result.ShouldContain("one");
        It should_calculate_line_5 = () => _result.ShouldContain("five");

        static Loesung17 _aufgabe;
        static IEnumerable<string> _result;
    }


    [Subject(typeof(Aufgabe17))]
    internal class When_task17_creates_lines_until_1000
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.GetLinesUntil(1000);
        It should_calculate_five_lines = () => _result.Count().ShouldEqual(1000);

        static Loesung17 _aufgabe;
        static IEnumerable<string> _result;
    }


    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_until_2
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateUntil(2);
        It should_calculate_five_lines = () => _result.ShouldEqual(6);

        static Loesung17 _aufgabe;
        static int _result;
    }


    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_until_9
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateUntil(9);
        It should_calculate_nine_lines = () => _result.ShouldEqual(36);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_until_19
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateUntil(19);
        It should_calculate_all_lines = () => _result.ShouldEqual(70+36);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_until_99
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateUntil(99);
        It should_calculate_all_lines = () => _result.ShouldEqual(9*36 + 70 + 10*46); // [9 * 1-10] + [1 * 11-19] + [10 * 20..90]

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_until_101
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateUntil(101);
        It should_calculate_all_lines = () => _result.ShouldEqual(9*36 + 70 + 10*46 + 10 + 16); 

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_for_101
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateFor(101);
        It should_calculate_all_lines = () => _result.ShouldEqual(16);

        static Loesung17 _aufgabe;
        static int _result;
    }

    [Subject(typeof(Aufgabe17))]
    internal class When_task17_calculates_for_100
    {
        Establish context = () => _aufgabe = new Aufgabe17();
        Because of = () => _result = _aufgabe.CalculateFor(100);
        It should_calculate_five_lines = () => _result.ShouldEqual(10);

        static Loesung17 _aufgabe;
        static int _result;
    }

}