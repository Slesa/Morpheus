using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(LoadCommand))]
    internal class When_creating_load_command : LoadCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("l");
        It should_have_description = () => Subject.Description.ShouldEqual("Load configuration file");

    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_no_filename : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals("No filename given")).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_invalid_filename : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>{"nofile"};
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals("File not found")).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_invalid_directory : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>{@"nodir\nofile"};
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals("Part of the file path not found")).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command : LoadCommandSpecsBase
    {
        Establish context = () =>
            {
                _tokens = new List<string> {SpecTestFile.FileName};
                SpecTestFile.Create();
            };
        Cleanup teardown = () => SpecTestFile.Remove();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_set_inifile = () => Environment.IniFile.ShouldNotBeNull();
        static List<string> _tokens;
    }



    class LoadCommandSpecsBase : WithFakes
    {
        Establish context = () =>
            {
                Input = An<IInput>();
                _specOutput = new SpecOutput();
                Environment = new AppEnvironment(Input, _specOutput);
                Subject = new LoadCommand();
            };

        protected static AppEnvironment Environment { get; set; }

        protected static string Output { get { return _specOutput.Buffer; } }
        protected static string[] OutputLines
        {
            get { return Output.Split('\n'); }
        }

        protected static IInput Input;
        protected static LoadCommand Subject;
        static SpecOutput _specOutput;
    }
}