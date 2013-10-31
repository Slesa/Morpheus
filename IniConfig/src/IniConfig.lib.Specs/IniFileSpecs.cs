using System.IO;
using System.Linq;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniFile))]
    internal class When_loading_not_existing_inifile : WithFakes
    {
        Because of = () => _error = Catch.Exception(() => IniFile.LoadFrom("NotExisting"));

        It should_fail_with_exception = () => _error.ShouldBeOfType(typeof(FileNotFoundException));

        static object _error;
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_empty_inifile : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("");

        It should_contain_one_line = () => Subject.Lines.Count().ShouldEqual(1);
        It should_not_contain_sections = () => Subject.Sections.ShouldBeEmpty();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_one_remark : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("; Remarks");

        It should_contain_the_line = () => Subject.Lines.Count().ShouldEqual(1);
        It should_not_contain_sections = () => Subject.Sections.ShouldBeEmpty();
    }




    [Subject(typeof(IniFile))]
    internal class When_loading_inifile : WithSubject<IniFile>
    {
        const string IniText = "\n" +
            "; The log file" + "\n" +
            "[Log]" + "\n" +
            "Level = All" + "\n" +
            "File = mylog.txt" + "\n" +
            "MaxSize = 512" + "\n" +
            "\n" +
            "; Define all devices for this application" + "\n" +
            "; It uses a printer and a display" + "\n" +
            "[Devices]" + "\n" +
            "printer = Printer1" + "\n" +
            "display = Display1" + "\n" +
            "\n" +
            "[Printer1]" + "\n" +
            "spool = spool\\printer1\\spool";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_the_lines = () => Subject.Lines.Count().ShouldEqual(15);
        It should_contain_log_section = () => Subject.FindSection("log").ShouldNotBeNull();
        It should_contain_log_remarks = () => Subject.FindSection("log").Remarks.First().ShouldEqual("The log file");
        It should_contain_log_level = () => Subject.FindSection("log").FindEntry("level").Value.ShouldEqual("All");
        It should_contain_log_file = () => Subject.FindSection("log").FindEntry("File").Value.ShouldEqual("mylog.txt");
        It should_contain_log_maxsize = () => Subject.FindSection("log").FindEntry("maxsize").AsInt.ShouldEqual(512);
        It should_contain_devices_section = () => Subject.FindSection("DEVICES").ShouldNotBeNull();
        It should_contain_devices_remark_1 = () => Subject.FindSection("DEVICES").Remarks[0].ShouldEqual("Define all devices for this application");
        It should_contain_devices_remark_2 = () => Subject.FindSection("DEVICES").Remarks[1].ShouldEqual("It uses a printer and a display");
        It should_contain_devices_printer = () => Subject.FindSection("DEVICES").FindEntry("Printer").Value.ShouldEqual("Printer1");
        It should_contain_devices_display = () => Subject.FindSection("DEVICES").FindEntry("Display").Value.ShouldEqual("Display1");
    }
}