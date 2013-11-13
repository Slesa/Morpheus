using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using IniConfig.lib;
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


    [Subject(typeof(RemoveEntryCommand))]
    internal class When_executing_remove_entry_command_without_config_file : RemoveEntryCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFileLoaded)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(RemoveEntryCommand))]
    internal class When_executing_remove_entry_command_without_section_name : RemoveEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string>();
                Environment.IniFile = An<IIniFile>();
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoSectionNameGiven)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(RemoveEntryCommand))]
    internal class When_executing_remove_entry_command_without_attribute : RemoveEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string> {"Section"};
                Environment.IniFile = An<IIniFile>();
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoAttributeGiven)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(RemoveEntryCommand))]
    internal class When_executing_remove_entry_command_for_unknown_section : RemoveEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string> {"Section", "Attribute", "Value"};
                Environment.IniFile = An<IIniFile>();
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Error_SectionNotFound)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(RemoveEntryCommand))]
    internal class When_executing_remove_entry_command : RemoveEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _inifile = new IniFile();
                _inifile.AddSection(SectionName);
                _inifile.AddEntry(SectionName,EntryName, "42");
                _tokens = new List<string> {SectionName, EntryName, "Value"};
                Environment.IniFile = _inifile;
            };

        Because of = () => Subject.Execute(_tokens, Environment);

        It should_remove_entry = () => _inifile.Sections.First().FindEntry(EntryName).ShouldBeNull();

        static List<string> _tokens;
        static IIniFile _inifile;
        const string SectionName = "Section";
        const string EntryName = "Attribute";
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