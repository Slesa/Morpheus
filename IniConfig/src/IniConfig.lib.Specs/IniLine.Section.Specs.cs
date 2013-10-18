using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_starts_with_section_sign_but_does_not_end_with_it : WithFakes
    {
        Because of = () => _subject = new IniLine("[A section");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_no_section = () => _subject.IsSection.ShouldBeFalse();
        It should_not_evaluate_section_name = () => _subject.Section.ShouldBeEmpty();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_ends_with_section_sign_but_does_not_start_with_it : WithFakes
    {
        Because of = () => _subject = new IniLine("A section]");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_no_section = () => _subject.IsSection.ShouldBeFalse();
        It should_not_evaluate_section_name = () => _subject.Section.ShouldBeEmpty();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_section : WithFakes
    {
        Because of = () => _subject = new IniLine("[A section]");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_section = () => _subject.IsSection.ShouldBeTrue();
        It should_evaluate_section_name = () => _subject.Section.ShouldEqual("A section");
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_section_starting_with_spaces : WithFakes
    {
        Because of = () => _subject = new IniLine("     [A section]");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_section = () => _subject.IsSection.ShouldBeTrue();
        It should_evaluate_section_name = () => _subject.Section.ShouldEqual("A section");
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_section_name_with_trailing_spaces : WithFakes
    {
        Because of = () => _subject = new IniLine("[   A section]");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_section = () => _subject.IsSection.ShouldBeTrue();
        It should_evaluate_section_name = () => _subject.Section.ShouldEqual("   A section");
        static IniLine _subject;
    }
}