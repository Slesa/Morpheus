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
    [Subject(typeof(CreateSectionCommand))]
    internal class When_creating_create_section_command : CreateSectionCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("cs");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.CreateSectionCommand_Description);
    }


    [Subject(typeof(CreateSectionCommand))]
    internal class When_executing_create_section_command_without_config_file : CreateSectionCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFileLoaded)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(ListSectionsCommand))]
    internal class When_executing_create_section_command_without_section_name : CreateSectionCommandSpecsBase
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


    [Subject(typeof(ListSectionsCommand))]
    internal class When_executing_create_section_command : CreateSectionCommandSpecsBase
    {
        Establish context = () =>
            {
                _sections = new List<IniSection>();
                _inifile = An<IIniFile>();
                _inifile.WhenToldTo(x => x.Sections).Return(_sections);
                _tokens = new List<string>{"Section"};
                Environment.IniFile = _inifile;
            };

        Because of = () => Subject.Execute(_tokens, Environment);

        It should_create_any_section = () => _sections.Count.ShouldEqual(1);
        It should_create_section = () => _sections[0].Name.ShouldEqual("Section");

        static List<string> _tokens;
        static IIniFile _inifile;
        static List<IniSection> _sections;
    }



    class CreateSectionCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new CreateSectionCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return string.IsNullOrEmpty(Output) ? new string[0] : Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static CreateSectionCommand Subject;
        static SpecOutput _specOutput;
    }
}