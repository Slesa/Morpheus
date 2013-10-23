using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Contracts;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(MainMenu))]
    internal class When_starting_mainmenu_once : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("q");
        Because of = () => Subject.Run();
        It should_print_two_lines = () => OutputLines.Count().ShouldEqual(2);
        It should_print_current_version = () => OutputLines.First().ShouldStartWith("IniConfig console interface, version");
        It should_print_prompt = () => OutputLines.Last().ShouldEqual("[<no file>] ? ");
    }

    [Subject(typeof(MainMenu))]
    internal class When_entering_help_in_mainmenu : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("? q");
        Because of = () =>
            {
                Subject.Run();
                _output = OutputLines.ToArray();
            };
        It should_print_two_lines = () => OutputLines.Count().ShouldEqual(2);
        It should_print_current_version = () => _output[0].ShouldStartWith("IniConfig console interface, version");
        It should_print_prompt = () => _output[1].ShouldEqual("[<no file>] ? ");

        static string[] _output;
    }




    internal class MainMenuSpecsBase : WithFakes
    {
        class SpecOutput : IOutput
        {
            public void WriteLine(string text)
            {
                Output += text + "\n";
            }

            public void Write(string text)
            {
                Output += text;
            }
        }

        Establish context = () =>
            {
                Input = An<IInput>();
                var output = new SpecOutput();
                Subject = new MainMenu(Input, output);
            };

        protected static IEnumerable<string> OutputLines { get { return Output.Split('\n'); }}
        protected static IInput Input;
        protected static string Output;
        protected static MainMenu Subject;
    }
}