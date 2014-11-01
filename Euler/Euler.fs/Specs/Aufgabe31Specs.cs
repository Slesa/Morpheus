using System.Collections.Generic;
using System.Linq;
using Aufgaben;
using Machine.Specifications;
using Microsoft.FSharp.Collections;

namespace Specs
{
    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_1
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(1, new FSharpList<int>(0, null)));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins).ToList();

        It should_have_2_ways = () => _result.Count().ShouldEqual(2);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_1 = () => _result.ShouldContain("200 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_100
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(100, new FSharpList<int>(0, null)));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins).ToList();

        It should_have_2_ways = () => _result.Count().ShouldEqual(2);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_100 = () => _result.ShouldContain("2 x 100");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_100_and_1
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(100, new FSharpList<int>(1, new FSharpList<int>(0, null))));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins).ToList();

        It should_compute_all_ways = () => _result.Count().ShouldEqual(4);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_100 = () => _result.ShouldContain("2 x 100");
        It should_compute_1 = () => _result.ShouldContain("200 x 1");
        It should_compute_100_and_1 = () => _result.ShouldContain("1 x 100 + 100 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_50_and_1
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(50, new FSharpList<int>(1, new FSharpList<int>(0, null))));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins).ToList();

        It should_compute_all_ways = () => _result.Count().ShouldEqual(6);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_50 = () => _result.ShouldContain("4 x 50");
        It should_compute_1 = () => _result.ShouldContain("200 x 1");
        It should_compute_3_times_50 = () => _result.ShouldContain("3 x 50 + 50 x 1");
        It should_compute_2_times_50 = () => _result.ShouldContain("2 x 50 + 100 x 1");
        It should_compute_1_time_50 = () => _result.ShouldContain("1 x 50 + 150 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_100_and_50_and_1
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(100, new FSharpList<int>(50, new FSharpList<int>(1, new FSharpList<int>(0, null)))));
            };

        Because of = () => _result = _aufgabe.Calculate(200, _coins).ToList();

        It should_compute_all_ways = () => _result.Count().ShouldEqual(10);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_50 = () => _result.ShouldContain("4 x 50");
        It should_compute_1 = () => _result.ShouldContain("200 x 1");

        It should_not_repeat_100 = () => _result.ShouldNotContain("1 x 100 + 1 x 100");
        It should_compute_1_time_100_with_50 = () => _result.ShouldContain("1 x 100 + 2 x 50");
        It should_compute_1_time_100_with_1 = () => _result.ShouldContain("1 x 100 + 100 x 1");
        It should_compute_1_time_100_with_50_and_1 = () => _result.ShouldContain("1 x 100 + 1 x 50 + 50 x 1");

        It should_not_repeat_50 = () => _result.ShouldNotContain("3 x 50 + 1 x 50");
        It should_compute_3_times_50 = () => _result.ShouldContain("3 x 50 + 50 x 1");
        It should_compute_2_times_50 = () => _result.ShouldContain("2 x 50 + 100 x 1");
        It should_compute_1_time_50 = () => _result.ShouldContain("1 x 50 + 150 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_50_with_50_and_20_and_1 
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(50, new FSharpList<int>(20 , new FSharpList<int>(1, new FSharpList<int>(0, null))));
            };

        Because of = () =>
            {
                _result = _aufgabe.Calculate(50, _coins).ToList();
                System.Diagnostics.Debug.WriteLine("Result: "+string.Join("\n", _result));
            };

        It should_compute_all_ways = () => _result.Count().ShouldEqual(4);

        It should_compute_1_time_50 = () => _result.ShouldContain("1 x 50");
        It should_compute_50_times_1 = () => _result.ShouldContain("50 x 1");
        It should_compute_2_times_20 = () => _result.ShouldContain("2 x 20 + 10 x 1");
        It should_compute_1_time_20 = () => _result.ShouldContain("1 x 20 + 30 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }

    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_200_with_200_and_100_and_50_and_20_and_1 
    {
        Establish context = () =>
            {
                _aufgabe = new Aufgabe31();
                _coins = new FSharpList<int>(200, new FSharpList<int>(100, new FSharpList<int>(50, new FSharpList<int>(20
                    , new FSharpList<int>(1, new FSharpList<int>(0, null))))));
            };

        Because of = () =>
            {
                _result = _aufgabe.Calculate(200, _coins).ToList();
                System.Diagnostics.Debug.WriteLine("Result: "+string.Join("\n", _result));
            };

        It should_compute_all_ways = () => _result.Count().ShouldEqual(41);

        It should_compute_1_time_100_with_50 = () => _result.ShouldContain("1 x 100 + 2 x 50");
        It should_compute_1_time_100_with_50_and_two_20 = () => _result.ShouldContain("1 x 100 + 1 x 50 + 2 x 20 + 10 x 1");
        It should_compute_1_time_100_with_50_and_one_20 = () => _result.ShouldContain("1 x 100 + 1 x 50 + 1 x 20 + 30 x 1");
        It should_compute_1_time_100_with_and_five_20 = () => _result.ShouldContain("1 x 100 + 5 x 20");
        It should_compute_1_time_100_with_and_four_20 = () => _result.ShouldContain("1 x 100 + 4 x 20 + 20 x 1");
        It should_compute_1_time_100_with_and_three_20 = () => _result.ShouldContain("1 x 100 + 3 x 20 + 40 x 1");
        It should_compute_1_time_100_with_and_two_20 = () => _result.ShouldContain("1 x 100 + 2 x 20 + 60 x 1");
        It should_compute_1_time_100_with_and_one_20 = () => _result.ShouldContain("1 x 100 + 1 x 20 + 80 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }
}