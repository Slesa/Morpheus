using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_starts_with_comment_sign : WithFakes
    {
        Because of = () => _subject = new IniLine("; a comment");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_comment = () => _subject.IsComment.ShouldBeTrue();
        It should_evaluate_comment = () => _subject.Comment.ShouldEqual("a comment");
        It should_not_see_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_starts_with_spaces_then_comment_sign : WithFakes
    {
        Because of = () => _subject = new IniLine("     ; a comment");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_comment = () => _subject.IsComment.ShouldBeTrue();
        It should_evaluate_comment = () => _subject.Comment.ShouldEqual("a comment");
        It should_not_see_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_does_not_start_with_comment_sign : WithFakes
    {
        Because of = () => _subject = new IniLine("[ a comment]");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_not_see_comment = () => _subject.IsComment.ShouldBeFalse();
        It should_not_evaluate_comment = () => _subject.Comment.ShouldBeEmpty();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_is_set_to_comment : WithFakes
    {
        Because of = () => _subject = new IniLine { Comment = "A comment" };
        It should_see_comment = () => _subject.IsComment.ShouldBeTrue();
        It should_set_content_to_comment = () => _subject.Content.ShouldEqual("; A comment");
        static IniLine _subject;
    }
}