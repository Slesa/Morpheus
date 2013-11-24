using System.Collections.Generic;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(QuitCommand))]
    internal class When_creating_quit_command : QuitCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("q");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.QuitCommand_Description);
    }


    [Subject(typeof(QuitCommand))]
    internal class When_executing_quit_command : QuitCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>(); 
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_not_set_quit_flag = () => Environment.QuitProgram.ShouldBeTrue();
        static List<string> _tokens;
    }


    [Subject(typeof(QuitCommand))]
    internal class When_executing_quit_command_but_created_section : QuitCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>(); 
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_not_set_quit_flag = () => Environment.QuitProgram.ShouldBeTrue();
        static List<string> _tokens;
    }




    class QuitCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new QuitCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static QuitCommand Subject;
        static SpecOutput _specOutput;
    }
}