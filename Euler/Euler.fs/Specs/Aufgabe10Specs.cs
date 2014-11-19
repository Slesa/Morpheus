using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe10))]
    public class When_summing_primes_below_10
    {
        Establish context = () => _aufgabe10 = new Aufgabe10();

        Because of = () => _result = _aufgabe10.Calculate(10);

        It should_do = () => _result.ShouldEqual(17);

        static Loesung10 _aufgabe10;
        static long _result;
    }
}