using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe7))]
    public class When_caluclating_1st_prime
    {
        Establish context = () => _aufgabe = new Aufgabe7();

        Because of = () => _result = _aufgabe.Calculate(1);

        It should_do = () => _result.ShouldEqual(2);

        static Loesung7 _aufgabe;
        static long _result;
    }


    [Subject(typeof(Aufgabe7))]
    public class When_caluclating_2nd_prime
    {
        Establish context = () => _aufgabe = new Aufgabe7();

        Because of = () => _result = _aufgabe.Calculate(2);

        It should_do = () => _result.ShouldEqual(3);

        static Loesung7 _aufgabe;
        static long _result;
    }


    [Subject(typeof(Aufgabe7))]
    public class When_caluclating_3rd_prime
    {
        Establish context = () => _aufgabe = new Aufgabe7();

        Because of = () => _result = _aufgabe.Calculate(3);

        It should_do = () => _result.ShouldEqual(5);

        static Loesung7 _aufgabe;
        static long _result;
    }


    [Subject(typeof(Aufgabe7))]
    public class When_caluclating_4th_prime
    {
        Establish context = () => _aufgabe = new Aufgabe7();

        Because of = () => _result = _aufgabe.Calculate(4);

        It should_do = () => _result.ShouldEqual(7);

        static Loesung7 _aufgabe;
        static long _result;
    }


    [Subject(typeof(Aufgabe7))]
    public class When_caluclating_5th_prime
    {
        Establish context = () => _aufgabe = new Aufgabe7();

        Because of = () => _result = _aufgabe.Calculate(5);

        It should_do = () => _result.ShouldEqual(11);

        static Loesung7 _aufgabe;
        static long _result;
    }
}