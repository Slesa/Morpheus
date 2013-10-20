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

        It should_contain_one_line = () => Subject.Lines.Count.ShouldEqual(1);
        It should_not_contain_sections = () => Subject.Sections.ShouldBeEmpty();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_one_remark : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("; Remarks");

        It should_contain_the_line = () => Subject.Lines.Count.ShouldEqual(1);
        It should_not_contain_sections = () => Subject.Sections.ShouldBeEmpty();
    }


    #region Sections

    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_one_section : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("[Section]");

        It should_contain_the_line = () => Subject.Lines.Count.ShouldEqual(1);
        It should_contain_the_section = () => Subject.Sections.Count.ShouldEqual(1);
        It should_find_the_section = () => Subject.FindSection("Section").ShouldNotBeNull();
        It should_find_the_section_case_independent = () => Subject.FindSection("section").ShouldNotBeNull();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_same_section_twice : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
                               "[Section]";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_two_lines = () => Subject.Lines.Count.ShouldEqual(2);
        It should_contain_one_section = () => Subject.Sections.Count.ShouldEqual(1);
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_section_with_remarks : WithSubject<IniFile>
    {
        const string IniText = "; Remarks" + "\n" +
                               "[Section]";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_two_lines = () => Subject.Lines.Count.ShouldEqual(2);
        It should_contain_the_section = () => Subject.Sections.Count.ShouldEqual(1);
        It should_contain_the_remarks = () => Subject.Sections.First().Remarks.ShouldContainOnly("Remarks");
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_section_with_remarks_separated_by_empty_lines : WithSubject<IniFile>
    {
        const string IniText = "; No Remarks" + "\n" +
            "\n" +
            "; Remarks" + "\n" +
            "[Section]";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_four_lines = () => Subject.Lines.Count.ShouldEqual(4);
        It should_contain_remarks_only = () => Subject.Sections.First().Remarks.ShouldContainOnly("Remarks");
    }

    #endregion


    #region Entries

    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_of_entry_without_section : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("entry = value");

        It should_contain_the_line = () => Subject.Lines.Count.ShouldEqual(1);
        It should_contain_the_section = () => Subject.Sections.ShouldBeEmpty();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_of_entry : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
            "entry = value";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_the_lines = () => Subject.Lines.Count.ShouldEqual(2);
        It should_contain_the_element = () => Subject.FindSection("Section").Elements.Count().ShouldEqual(1);
        It should_find_the_element = () => Subject.FindSection("Section").FindElement("entry").Value.ShouldEqual("value");
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_full_of_entries : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
            "1 = true" + "\n" +
            "two = 42" + "\n" +
            "3three = 42.0";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_all_lines = () => Subject.Lines.Count.ShouldEqual(4);
        It should_contain_the_elements = () => Subject.FindSection("Section").Elements.Count().ShouldEqual(3);
        It should_find_first_element = () => Subject.FindSection("Section").FindElement("1").AsBool.ShouldBeTrue();
        It should_find_second_element = () => Subject.FindSection("Section").FindElement("two").AsInt.ShouldEqual(42);
        It should_find_third_element = () => Subject.FindSection("Section").FindElement("3three").AsDouble.ShouldEqual(42.0);
    }

    #endregion


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

        It should_contain_the_lines = () => Subject.Lines.Count.ShouldEqual(15);
        It should_contain_log_section = () => Subject.FindSection("log").ShouldNotBeNull();
        It should_contain_log_remarks = () => Subject.FindSection("log").Remarks.First().ShouldEqual("The log file");
        It should_contain_log_level = () => Subject.FindSection("log").FindElement("level").Value.ShouldEqual("All");
        It should_contain_log_file = () => Subject.FindSection("log").FindElement("File").Value.ShouldEqual("mylog.txt");
        It should_contain_log_maxsize = () => Subject.FindSection("log").FindElement("maxsize").AsInt.ShouldEqual(512);
        It should_contain_devices_section = () => Subject.FindSection("DEVICES").ShouldNotBeNull();
        It should_contain_devices_remark_1 = () => Subject.FindSection("DEVICES").Remarks[0].ShouldEqual("Define all devices for this application");
        It should_contain_devices_remark_2 = () => Subject.FindSection("DEVICES").Remarks[1].ShouldEqual("It uses a printer and a display");
        It should_contain_devices_printer = () => Subject.FindSection("DEVICES").FindElement("Printer").Value.ShouldEqual("Printer1");
        It should_contain_devices_display = () => Subject.FindSection("DEVICES").FindElement("Display").Value.ShouldEqual("Display1");
    }
}