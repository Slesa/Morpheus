using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(ListEntriesCommand))]
    internal class When_creating_list_entries_command : ListEntriesCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("le");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.ListEntriesCommand_Description);
    }


    class ListEntriesCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new ListEntriesCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static ListEntriesCommand Subject;
        static SpecOutput _specOutput;
    }
}