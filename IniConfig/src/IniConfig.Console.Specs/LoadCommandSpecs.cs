using System.Collections.Generic;
using System.Linq;
using IniConfig.Console.lib;
using IniConfig.Console.lib.Commands;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Resources;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Console.Specs
{
    [Subject(typeof(LoadCommand))]
    internal class When_creating_load_command : LoadCommandSpecsBase
    {
        It should_have_shortcut = () => Subject.Shortcut.ShouldEqual("l");
        It should_have_description = () => Subject.Description.ShouldEqual(Strings.LoadCommand_Description);
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_no_filename : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Warning_NoFilenameGiven)).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_invalid_filename : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>{"nofile"};
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Error_FileNotFound)).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof(LoadCommand))]
    internal class When_executing_load_command_with_invalid_directory : LoadCommandSpecsBase
    {
        Establish context = () => _tokens = new List<string>{@"nodir\nofile"};
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_print_error = () => OutputLines.FirstOrDefault(x => x.Equals(Strings.Error_DirectoryNotFound)).ShouldNotBeNull();
        It should_not_set_inifile = () => Environment.IniFile.ShouldBeNull();
        static List<string> _tokens;
    }


    [Subject(typeof (LoadCommand))]
    internal class When_executing_load_command : LoadCommandSpecsBase
    {
        Establish context = () =>
            {
                _specTestFile = new SpecTestFile(typeof (When_executing_load_command));
                _tokens = new List<string> {_specTestFile.FileName};
                _specTestFile.Create();
            };

        Cleanup teardown = () => _specTestFile.Remove();
        Because of = () => Subject.Execute(_tokens, Environment);
        It should_set_inifile = () => Environment.IniFile.ShouldNotBeNull();
        static List<string> _tokens;
        static SpecTestFile _specTestFile;
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