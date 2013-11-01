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
    [Subject(typeof(ListEntriesCommand))]
    internal class When_creating_list_entries_command : ListEntriesCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("le");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.ListEntriesCommand_Description);
    }


    [Subject(typeof(ListEntriesCommand))]
    internal class When_executing_list_entries_command_without_config_file : ListEntriesCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFileLoaded)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(ListEntriesCommand))]
    internal class When_executing_list_entries_command_without_section_name : ListEntriesCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string>();
                _inifile = An<IIniFile>();
                Environment.IniFile = _inifile;
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoSectionNameGiven)).ShouldNotBeNull();
        static List<string> _tokens;
        static IIniFile _inifile;
    }


    [Subject(typeof(ListEntriesCommand))]
    internal class When_executing_list_entries_command_with_empty_config_file : ListEntriesCommandSpecsBase
    {
        Establish context = () =>
        {
            _tokens = new List<string>{"Section"};
            _inifile = An<IIniFile>();
            _inifile.WhenToldTo(x => x.Sections).Return(new List<IniSection>());
            Environment.IniFile = _inifile;
        };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Error_SectionNotFound)).ShouldNotBeNull();
        static List<string> _tokens;
        static IIniFile _inifile;
    }


    [Subject(typeof(ListEntriesCommand))]
    internal class When_executing_list_entries_command_with_config_file : ListEntriesCommandSpecsBase
    {
        Establish context = () =>
        {
            _inifile = new IniFile();
            var section = _inifile.AddSection(LogSection);
            section.AddElement("Level", "All").AddElement("MaxSize", "512");

            _tokens = new List<string>{"log"};
            Environment.IniFile = _inifile;
        };

        Because of = () => Subject.Execute(_tokens, Environment);

        It should_print_sections = () => OutputLines.Count().ShouldEqual(6);
        It should_print_header = () => OutputLines[0].ShouldEqual(string.Format(Strings.ListEntriesCommand_Header,LogSection));
        It should_print_level_entry = () => OutputLines[1].ShouldEqual("Level = All");
        It should_print_maxsize_entry = () => OutputLines[2].ShouldEqual("MaxSize = 512");
        const string LogSection = "Log";
        static List<string> _tokens;
        static IIniFile _inifile;
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