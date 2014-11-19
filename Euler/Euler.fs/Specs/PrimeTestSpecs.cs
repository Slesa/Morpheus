using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Numbers))]
    internal class When_testing_2_as_prime
    {
        Establish context = () => _numbers = new Numbers();

        Because of = () => _result = _numbers.IsPrime(2);

        It should_say_yes = () => _result.ShouldBeTrue();

        static INumbers _numbers;
        static bool _result;
    }

    [Subject(typeof(Numbers))]
    internal class When_testing_3_as_prime
    {
        Establish context = () => _numbers = new Numbers();

        Because of = () => _result = _numbers.IsPrime(3);

        It should_say_yes = () => _result.ShouldBeTrue();

        static INumbers _numbers;
        static bool _result;
    }

    [Subject(typeof(Numbers))]
    internal class When_testing_4_as_prime
    {
        Establish context = () => _numbers = new Numbers();

        Because of = () => _result = _numbers.IsPrime(4);

        It should_say_no = () => _result.ShouldBeFalse();

        static INumbers _numbers;
        static bool _result;
    }

    [Subject(typeof(Numbers))]
    internal class When_testing_11_as_prime
    {
        Establish context = () => _numbers = new Numbers();

        Because of = () => _result = _numbers.IsPrime(11);

        It should_say_yes = () => _result.ShouldBeTrue();

        static INumbers _numbers;
        static bool _result;
    }

    [Subject(typeof(Numbers))]
    internal class When_testing_35_as_prime
    {
        Establish context = () => _numbers = new Numbers();

        Because of = () => _result = _numbers.IsPrime(35);

        It should_say_no = () => _result.ShouldBeFalse();

        static INumbers _numbers;
        static bool _result;
    }
}