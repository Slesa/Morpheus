using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    #region Comments

    [Subject(typeof(IniLine))]
    class When_line_starts_with_comment_sign : WithFakes
    {
        Because of = () => _subject = new IniLine("; a comment");
        It see_comment = () => _subject.IsComment.ShouldBeTrue();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_starts_with_spaces_then_comment_sign : WithFakes
    {
        Because of = () => _subject = new IniLine("     ; a comment");
        It see_comment = () => _subject.IsComment.ShouldBeTrue();
        static IniLine _subject;
    }

    #endregion

    #region Section

    [Subject(typeof(IniLine))]
    class When_line_starts_with_section_sign_but_does_not_end_with_it : WithFakes
    {
        Because of = () => _subject = new IniLine("[A section");
        It see_no_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_ends_with_section_sign_but_does_not_start_with_it : WithFakes
    {
        Because of = () => _subject = new IniLine("A section]");
        It see_no_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_section : WithFakes
    {
        Because of = () => _subject = new IniLine("[A section]");
        It see_section = () => _subject.IsSection.ShouldBeTrue();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_section_starting_with_spaces : WithFakes
    {
        Because of = () => _subject = new IniLine("     [A section]");
        It see_section = () => _subject.IsSection.ShouldBeTrue();
        static IniLine _subject;
    }

    #endregion

    [Subject(typeof(IniLine))]
    class When_line_contains_garbage : WithFakes
    {
        Because of = () => _subject = new IniLine("garbage");
        It see_no_comment = () => _subject.IsComment.ShouldBeFalse();
        It see_no_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }
}