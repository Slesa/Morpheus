using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_is_empty : WithFakes
    {
        Because of = () => _subject = new IniLine("");
        It should_see_empty_line = () => _subject.IsEmpty.ShouldBeTrue();
        It should_not_see_comment = () => _subject.IsComment.ShouldBeFalse();
        It should_not_see_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_spaces : WithFakes
    {
        Because of = () => _subject = new IniLine("       ");
        It should_see_empty_line = () => _subject.IsEmpty.ShouldBeTrue();
        It should_not_see_comment = () => _subject.IsComment.ShouldBeFalse();
        It should_not_see_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }
}