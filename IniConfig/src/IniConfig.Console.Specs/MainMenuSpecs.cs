using System.Linq;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(MainMenu))]
    internal class When_starting_mainmenu_once : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("q");
        Because of = () => Subject.Run();
        It should_print_two_lines = () => OutputLines.Count().ShouldEqual(3);
        It should_print_current_version = () => OutputLines.ToArray()[0].ShouldStartWith("IniConfig console interface, version");
        It should_print_prompt = () => OutputLines[1].ShouldEqual("[<no file>] ? ");
    }


    [Subject(typeof(MainMenu))]
    internal class When_entering_help_in_mainmenu : MainMenuSpecsBase
    {
        Establish context = () => Input.WhenToldTo(x => x.ReadLine()).Return("? q");
        Because of = () => Subject.Run();
        //It should_print_the_lines = () => OutputLines.Count().ShouldEqual(12);
        It should_print_current_version = () => OutputLines[0].ShouldStartWith("IniConfig console interface, version");
        It should_print_prompt = () => OutputLines[1].ShouldEqual("[<no file>] ? ");
        It should_print_syntax_line = () => OutputLines.FirstOrDefault(x => x.StartsWith("Syntax:")).ShouldNotBeNull();
        It should_print_help_line = () => OutputLines.FirstOrDefault(x => x.StartsWith("  ?")).ShouldNotBeNull();
        It should_print_quit_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new QuitCommand().Shortcut)).ShouldNotBeNull();
        It should_print_quit_description = () => OutputLines.FirstOrDefault(x => x.Contains(new QuitCommand().Description)).ShouldNotBeNull();
        It should_print_load_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new LoadCommand().Shortcut)).ShouldNotBeNull();
        It should_print_load_description = () => OutputLines.FirstOrDefault(x => x.Contains(new LoadCommand().Description)).ShouldNotBeNull();
        It should_print_save_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new SaveCommand().Shortcut)).ShouldNotBeNull();
        It should_print_save_description = () => OutputLines.FirstOrDefault(x => x.Contains(new SaveCommand().Description)).ShouldNotBeNull();
        It should_print_list_sections_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new ListSectionsCommand().Shortcut)).ShouldNotBeNull();
        It should_print_list_sections_description = () => OutputLines.FirstOrDefault(x => x.Contains(new ListSectionsCommand().Description)).ShouldNotBeNull();
        It should_print_create_section_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new CreateSectionCommand().Shortcut)).ShouldNotBeNull();
        It should_print_create_section_description = () => OutputLines.FirstOrDefault(x => x.Contains(new CreateSectionCommand().Description)).ShouldNotBeNull();
        It should_print_remove_section_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new RemoveSectionCommand().Shortcut)).ShouldNotBeNull();
        It should_print_remove_section_description = () => OutputLines.FirstOrDefault(x => x.Contains(new RemoveSectionCommand().Description)).ShouldNotBeNull();
        It should_print_list_entries_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new ListEntriesCommand().Shortcut)).ShouldNotBeNull();
        It should_print_list_entries_description = () => OutputLines.FirstOrDefault(x => x.Contains(new ListEntriesCommand().Description)).ShouldNotBeNull();
        It should_print_create_entry_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new CreateEntryCommand().Shortcut)).ShouldNotBeNull();
        It should_print_create_entry_description = () => OutputLines.FirstOrDefault(x => x.Contains(new CreateEntryCommand().Description)).ShouldNotBeNull();
        It should_print_remove_entry_shortcut = () => OutputLines.FirstOrDefault(x => x.StartsWith("  " + new RemoveEntryCommand().Shortcut)).ShouldNotBeNull();
        It should_print_remove_entry_description = () => OutputLines.FirstOrDefault(x => x.Contains(new RemoveEntryCommand().Description)).ShouldNotBeNull();
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
        It should_print_error = () => _output.FirstOrDefault(x => x.Equals(Strings.Warning_NoFilenameGiven)).ShouldNotBeNull();

        static string[] _output;
    }




    internal class MainMenuSpecsBase : WithFakes
    {

        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Subject = new MainMenu(Input, _specOutput);
                Subject.SetIsInTestMode();
            };

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines { get { return Output.Split('\n'); } }
        protected static IInput Input;
        protected static MainMenu Subject;
        static SpecOutput _specOutput;

        protected static void DebugOutput()
        {
            foreach(var line in OutputLines)
                System.Diagnostics.Debug.WriteLine(line);
        }

    }
}