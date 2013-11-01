using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(RemoveSectionCommand))]
    internal class When_creating_remove_entry_command : RemoveEntryCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("re");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.RemoveEntryCommand_Description);
    }



    class RemoveEntryCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new RemoveEntryCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return string.IsNullOrEmpty(Output) ? new string[0] : Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static RemoveEntryCommand Subject;
        static SpecOutput _specOutput;
    }
}