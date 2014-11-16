using System.Collections.Generic;
using System.Linq;
using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe3))]
    internal class When_calculating_largest_prime_factor_for_9
    {
        Establish context = () => _aufgabe = new Aufgabe3();

        Because of = () => _result = _aufgabe.Calculate(9L);

        It should_find_result = () => _result.ShouldEqual(3);

        static Loesung3 _aufgabe;
        static long _result;
    }

    [Subject(typeof(Aufgabe3))]
    internal class When_calculating_largest_prime_factor_for_13195
    {
        Establish context = () => _aufgabe = new Aufgabe3();

        Because of = () => _result = _aufgabe.Calculate(13195L);

        It should_find_result = () => _result.ShouldEqual(29);

        static Loesung3 _aufgabe;
        static long _result;
    }

    [Subject(typeof(Aufgabe3))]
    internal class When_calculating_all_prime_factors_for_13195
    {
        Establish context = () => _aufgabe = new Aufgabe3();

        Because of = () => _result = _aufgabe.FindPrimes(13195L);

        It should_find_all = () => _result.Count().ShouldEqual(4);
        It should_find_5 = () => _result.ShouldContain(5);
        It should_find_7 = () => _result.ShouldContain(7);
        It should_find_13 = () => _result.ShouldContain(13);
        It should_find_29 = () => _result.ShouldContain(29);

        static Loesung3 _aufgabe;
        static IEnumerable<long> _result;
    }
}