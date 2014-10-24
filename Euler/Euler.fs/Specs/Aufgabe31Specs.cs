using Aufgaben;
using Machine.Specifications;

namespace Specs
{
    [Subject(typeof(Aufgabe31))]
    internal class When_dispensing_only_1p
    {
        Establish context = () => _aufgabe = new Aufgabe31();

        static Loesung31 _aufgabe;
    }
}