using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_contains_garbage : WithFakes
    {
        Because of = () => _subject = new IniLine("garbage");
        It should_not_see_empty_line = () => _subject.IsEmpty.ShouldBeFalse();
        It should_see_no_comment = () => _subject.IsComment.ShouldBeFalse();
        It should_see_no_section = () => _subject.IsSection.ShouldBeFalse();
        static IniLine _subject;
    }
}