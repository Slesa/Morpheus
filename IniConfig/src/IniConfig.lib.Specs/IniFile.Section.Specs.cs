using System.Collections.Generic;
using System.Linq;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_one_section : WithSubject<IniFile>
    {
        Because of = () => Subject.LoadFromText("[Section]");

        It should_contain_the_line = () => Subject.Lines.Count().ShouldEqual(1);
        It should_contain_the_section = () => Subject.Sections.Count().ShouldEqual(1);
        It should_find_the_section = () => Subject.FindSection("Section").ShouldNotBeNull();
        It should_find_the_section_case_independent = () => Subject.FindSection("section").ShouldNotBeNull();
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_same_section_twice : WithSubject<IniFile>
    {
        const string IniText = "[Section]" + "\n" +
                               "[Section]";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_contain_one_section = () => Subject.Sections.Count().ShouldEqual(1);
    }


    [Subject(typeof(IniFile))]
    internal class When_loading_inifile_with_section_with_remarks : WithSubject<IniFile>
    {
        const string IniText = "; Remarks" + "\n" +
                               "[Section]";
        Because of = () => Subject.LoadFromText(IniText);

        It should_contain_two_lines = () => Subject.Lines.Count().ShouldEqual(2);
        It should_contain_the_section = () => Subject.Sections.Count().ShouldEqual(1);
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

        It should_contain_four_lines = () => Subject.Lines.Count().ShouldEqual(4);
        It should_contain_remarks_only = () => Subject.Sections.First().Remarks.ShouldContainOnly("Remarks");
    }


    [Subject(typeof(IniFile))]
    internal class When_adding_section_to_empty_inifile : WithSubject<IniFile>
    {
        Because of = () => _section = Subject.AddSection("Section");
        It should_contain_one_line = () => Subject.Lines.Count().ShouldEqual(1);
        It should_contain_section = () => Subject.FindSection("Section").ShouldEqual(_section);
        static IniSection _section;
    }


    [Subject(typeof(IniFile))]
    internal class When_adding_section_with_remarks_to_empty_inifile : WithSubject<IniFile>
    {
        Because of = () => _section = Subject.AddSection("Section", new List<string>{"Remark 1", "Remark 2"});
        It should_contain_one_line = () => Subject.Lines.Count().ShouldEqual(3);
        It should_contain_section = () => Subject.FindSection("Section").ShouldEqual(_section);
        It should_contain_remark1 = () => _section.Remarks.ShouldContain("Remark 1");
        It should_contain_remark2 = () => _section.Remarks.ShouldContain("Remark 2");
        It should_contain_remark1_line = () => Subject.Lines.ToArray()[0].Comment.ShouldEqual("Remark 1");
        It should_contain_remark2_line = () => Subject.Lines.ToArray()[1].Comment.ShouldEqual("Remark 2");
        It should_contain_section_line = () => Subject.Lines.ToArray()[2].Section.ShouldEqual("Section");
        static IniSection _section;
    }
}