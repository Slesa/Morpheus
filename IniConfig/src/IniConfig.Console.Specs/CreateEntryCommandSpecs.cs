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
    [Subject(typeof(CreateEntryCommand))]
    internal class When_creating_create_entry_command : CreateEntryCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("ce");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.CreateEntryCommand_Description);
    }


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command_without_config_file : CreateEntryCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFileLoaded)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command_without_section_name : CreateEntryCommandSpecsBase
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


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command_without_attribute : CreateEntryCommandSpecsBase
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


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command_without_value : CreateEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string> {"Section", "Attribute"};
                Environment.IniFile = An<IIniFile>();
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoValueGiven)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command_for_unknown_section : CreateEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string> { "Section", "Attribute", "Value" };
                Environment.IniFile = An<IIniFile>();
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Error_SectionNotFound)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(CreateEntryCommand))]
    internal class When_executing_create_entry_command : CreateEntryCommandSpecsBase
    {
        Establish context = () =>
            {
                _inifile = new IniFile();
                _inifile.AddSection(SectionName);
                _tokens = new List<string> {SectionName, EntryName, "Value"};
                Environment.IniFile = _inifile;
            };

        Because of = () => Subject.Execute(_tokens, Environment);

        It should_create_entry = () => _inifile.Sections.First().FindEntry(EntryName).ShouldNotBeNull();

        static List<string> _tokens;
        static IIniFile _inifile;
        const string SectionName = "Section";
        const string EntryName = "Attribute";
    }



    class CreateEntryCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new CreateEntryCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return string.IsNullOrEmpty(Output) ? new string[0] : Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static CreateEntryCommand Subject;
        static SpecOutput _specOutput;
    }
}