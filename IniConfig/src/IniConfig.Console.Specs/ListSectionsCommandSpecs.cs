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
    [Subject(typeof(ListSectionsCommand))]
    internal class When_creating_list_sections_command : ListSectionsCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("ls");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.ListSectionsCommand_Description);
    }


    [Subject(typeof(ListSectionsCommand))]
    internal class When_executing_list_sections_command_without_config_file : ListSectionsCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFileLoaded)).ShouldNotBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(ListSectionsCommand))]
    internal class When_executing_list_sections_command_with_empty_config_file : ListSectionsCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string>();
                _inifile = An<IIniFile>();
                _inifile.WhenToldTo(x => x.Sections).Return(new List<IniSection>());
                Environment.IniFile = _inifile;
            };
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_not_print = () => OutputLines/*.Where(x=>!string.IsNullOrEmpty(x))*/.ShouldBeEmpty();
        static List<string> _tokens;
        static IIniFile _inifile;
    }


    [Subject(typeof(ListSectionsCommand))]
    internal class When_executing_list_sections_command_with_config_file : ListSectionsCommandSpecsBase
    {
        Establish context = () =>
            {
                _inifile = An<IIniFile>();
                _inifile.WhenToldTo(x=>x.Sections).Return(new List<IniSection>
                    {
                        new IniSection{Name="Log"},
                        new IniSection{Name="Printer"},
                        new IniSection{Name="Display"},
                    });
                _tokens = new List<string>();
                Environment.IniFile = _inifile;
            };

        Because of = () => Subject.Execute(_tokens, Environment);

        It should_print_sections = () => OutputLines.Count().ShouldEqual(4);
        It should_print_log_section = () => OutputLines.FirstOrDefault(x=>x.Equals("[Log]")).ShouldNotBeNull();
        It should_print_printer_section = () => OutputLines.FirstOrDefault(x=>x.Equals("[Printer]")).ShouldNotBeNull();
        It should_print_display_section = () => OutputLines.FirstOrDefault(x=>x.Equals("[Display]")).ShouldNotBeNull();
        
        static List<string> _tokens;
        static IIniFile _inifile;
    }





    class ListSectionsCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new ListSectionsCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return string.IsNullOrEmpty(Output) ? new string[0] : Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static ListSectionsCommand Subject;
        static SpecOutput _specOutput;
    }
}