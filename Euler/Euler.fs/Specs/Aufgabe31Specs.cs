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
        It should_compute_100_and_1 = () => _result.ShouldContain("1 x 100+100 x 1");

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
        It should_compute_3_times_50 = () => _result.ShouldContain("3 x 50+50 x 1");
        It should_compute_2_times_50 = () => _result.ShouldContain("2 x 50+100 x 1");
        It should_compute_1_time_50 = () => _result.ShouldContain("1 x 50+150 x 1");

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

        It should_compute_all_ways = () => _result.Count().ShouldEqual(6);
        It should_compute_200 = () => _result.ShouldContain("1 x 200");
        It should_compute_50 = () => _result.ShouldContain("4 x 50");
        It should_compute_1 = () => _result.ShouldContain("200 x 1");
        It should_compute_3_times_50 = () => _result.ShouldContain("3 x 50+50 x 1");
        It should_compute_2_times_50 = () => _result.ShouldContain("2 x 50+100 x 1");
        It should_compute_1_time_50 = () => _result.ShouldContain("1 x 50+150 x 1");

        static Loesung31 _aufgabe;
        static IEnumerable<string> _result;
        static FSharpList<int> _coins;
    }
}