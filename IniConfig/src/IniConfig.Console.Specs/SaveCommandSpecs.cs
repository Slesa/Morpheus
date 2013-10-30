using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(SaveCommand))]
    internal class When_creating_save_command : SaveCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("s");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.SaveCommand_Description);
    }



    class SaveCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new SaveCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static SaveCommand Subject;
        static SpecOutput _specOutput;
    }
}