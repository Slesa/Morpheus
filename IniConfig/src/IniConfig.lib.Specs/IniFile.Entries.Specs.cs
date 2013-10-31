using System.Linq;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_of_entry_without_section : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("entry = value");

        It should_contain_the_line = () => Subject.Lines.Count().ShouldEqual(1);
        It should_contain_the_section = () => Subject.Sections.ShouldBeEmpty();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_of_entry : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
            "entry = value";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_the_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_contain_the_element = () => Subject.FindSection("Section").Entries.Count().ShouldEqual(1);
        It should_find_the_element = () => Subject.FindSection("Section").FindEntry("entry").Value.ShouldEqual("value");
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_full_of_entries : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
            "1 = true" + "\n" +
            "two = 42" + "\n" +
            "3three = 42.0";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_all_lines = () => Subject.Lines.Count().ShouldEqual(4);
        It should_contain_the_elements = () => Subject.FindSection("Section").Entries.Count().ShouldEqual(3);
        It should_find_first_element = () => Subject.FindSection("Section").FindEntry("1").AsBool.ShouldBeTrue();
        It should_find_second_element = () => Subject.FindSection("Section").FindEntry("two").AsInt.ShouldEqual(42);
        It should_find_third_element = () => Subject.FindSection("Section").FindEntry("3three").AsDouble.ShouldEqual(42.0);
    }
}