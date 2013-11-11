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


    [Subject(typeof(IniFile))]
    internal class When_searching_entry_in_unexisting_section : WithSubject<IniFile>
    {
        Because of = () => _entry = Subject.FindEntry("Section", "Entry");
        It should_return_null = () => _entry.ShouldBeNull();
        static IniEntry _entry;
    }


    [Subject(typeof(IniFile))]
    internal class When_searching_unexisting_entry_in_existing_section : WithSubject<IniFile>
    {
        Establish context = () => Subject.AddSection("Section");
        Because of = () => _entry = Subject.FindEntry("Section", "Entry");
        It should_return_null = () => _entry.ShouldBeNull();
        static IniEntry _entry;
    }


    [Subject(typeof(IniFile))]
    internal class When_searching_existing_entry : WithSubject<IniFile>
    {
        Establish context = () => Subject.AddSection("Section").AddEntry("Entry","Value");
        Because of = () => _entry = Subject.FindEntry("Section","Entry");
        It should_return_section = () => _entry.ShouldNotBeNull();
        static IniEntry _entry;
    }


    [Subject(typeof(IniFile))]
    internal class When_adding_entry_to_unexisting_section : WithSubject<IniFile>
    {
        Because of = () => _entry = Subject.AddEntry(SectionName, Attribute, Value);
        It should_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_create_section = () => Subject.FindSection(SectionName).ShouldNotBeNull();
        It should_add_entry = () => Subject.FindEntry(SectionName, Attribute).ShouldEqual(_entry);
        static IniEntry _entry;
        const string SectionName = "Section";
        const string Attribute = "Attribute";
        const string Value = "Value";
    }


    [Subject(typeof(IniFile))]
    internal class When_adding_entry_to_empty_section : WithSubject<IniFile>
    {
        Establish context = ()=> Subject.AddSection(SectionName);
        Because of = () => _entry = Subject.AddEntry(SectionName, Attribute, Value);
        It should_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_add_entry = () => Subject.FindEntry(SectionName, Attribute).ShouldEqual(_entry);
        static IniEntry _entry;
        const string SectionName = "Section";
        const string Attribute = "Attribute";
        const string Value = "Value";
    }


    [Subject(typeof(IniFile))]
    internal class When_removing_unsexisting_entry : WithSubject<IniFile>
    {
        Establish context = () =>
            {
                Subject.AddSection(SectionName);
                Subject.AddEntry(SectionName, Attribute, Value);
            };
        Because of = () => Subject.RemoveEntry(SectionName, UnexistingAttribute);
        It should_still_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_still_contain_section = () => Subject.FindSection(SectionName).ShouldNotBeNull();
        It should_not_remove_existing_entry = () => Subject.FindEntry(SectionName, Attribute).ShouldNotBeNull();
        static IniEntry _entry;
        const string SectionName = "Section";
        const string Attribute = "Attribute";
        const string UnexistingAttribute = "NotExisting";
        const string Value = "Value";
    }


    [Subject(typeof(IniFile))]
    internal class When_removing_entry : WithSubject<IniFile>
    {
        Establish context = () =>
            {
                Subject.AddSection(SectionName);
                Subject.AddEntry(SectionName, Attribute, Value);
            };
        Because of = () => Subject.RemoveEntry(SectionName, Attribute);
        It should_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(1);
        It should_still_contain_section = () => Subject.FindSection(SectionName).ShouldNotBeNull();
        It should_remove_entry = () => Subject.FindEntry(SectionName, Attribute).ShouldBeNull();
        static IniEntry _entry;
        const string SectionName = "Section";
        const string Attribute = "Attribute";
        const string Value = "Value";
    }
}