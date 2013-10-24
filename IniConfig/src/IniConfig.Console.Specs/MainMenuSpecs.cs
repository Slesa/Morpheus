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
        Because of = () =>
            {
                Subject.Run();
                DebugOutput();
            };
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
        It should_print_the_lines = () => OutputLines.Count().ShouldEqual(6);
        It should_print_current_version = () => _output[0].ShouldStartWith("IniConfig console interface, version");
        It should_print_prompt = () => _output[1].ShouldEqual("[<no file>] ? ");
        It should_print_syntax_line = () => _output.FirstOrDefault(x => x.Contains("Syntax:")).ShouldNotBeNull();
        It should_print_help_line = () => _output.FirstOrDefault(x => x.Contains("  ?")).ShouldNotBeNull();
        It should_print_quit_line = () => _output.FirstOrDefault(x => x.Contains("  q")).ShouldNotBeNull();

        static string[] _output;
    }


    [Subject(typeof(MainMenu))]
    internal class When_entering_unknown_command_in_mainmenu : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("42 q");
        Because of = () =>
            {
                Subject.Run();
                _output = OutputLines.ToArray();
            };
        It should_print_unknown_command = () => _output.FirstOrDefault(x => x.Equals("Unknown command 42")).ShouldNotBeNull();

        static string[] _output;
    }


    [Subject(typeof(MainMenu))]
    internal class When_calling_load_command_with_no_filename_in_mainmenu : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("l q");
        Because of = () =>
            {
                Subject.Run();
                _output = OutputLines.ToArray();
            };
        It should_print_error = () => _output.FirstOrDefault(x => x.Equals("No filename given")).ShouldNotBeNull();

        static string[] _output;
    }




    internal class MainMenuSpecsBase : WithFakes
    {
        class SpecOutput : IOutput
        {
            public IOutput WriteLine(string text)
            {
                Output += text + "\n";
                return this;
            }

            public IOutput Write(string text)
            {
                Output += text;
                return this;
            }
        }

        Establish context = () =>
            {
                Input = An<IInput>();
                var output = new SpecOutput();
                Subject = new MainMenu(Input, output);
                Subject.SetIsInTestMode();
            };

        Cleanup teardown = () =>
            {
                Output = string.Empty;
            };

        protected static IEnumerable<string> OutputLines { get { return Output.Split('\n'); }}
        protected static IInput Input;
        protected static string Output;
        protected static MainMenu Subject;

        protected static void DebugOutput()
        {
            foreach(var line in OutputLines)
                System.Diagnostics.Debug.WriteLine(line);
        }

    }
}