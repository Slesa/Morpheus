using System;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_contains_value_but_starts_with_comment_sign : WithFakes
    {
        Establish context = () => _subject = new IniLine("; entry = value");
        Because of = () => _error = Catch.Exception(() => _x = _subject.Value);
        It should_fail = () => _error.ShouldBeOfType<InvalidOperationException>();
        It should_fail_with_message = () => _error.Message.ShouldEqual("'; entry = value': entry has invalid format");
        static IniLine _subject;
        static string _x;
        static Exception _error;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_value_but_starts_with_section_open_sign : WithFakes
    {
        Establish context = () => _subject = new IniLine("[ entry = value");
        Because of = () => _error = Catch.Exception(() => x = _subject.Value);
        It should_fail = () => _error.ShouldBeOfType<InvalidOperationException>();
        It should_fail_with_message = () => _error.Message.ShouldEqual("'[ entry = value': entry has invalid format");
        static IniLine _subject;
        static string x;
        static Exception _error;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_value_but_starts_with_section_close_sign : WithFakes
    {
        Establish context = () => _subject = new IniLine("] entry = value");
        Because of = () => _error = Catch.Exception(() => x = _subject.Value);
        It should_fail = () => _error.ShouldBeOfType<InvalidOperationException>();
        It should_fail_with_message = () => _error.Message.ShouldEqual("'] entry = value': entry has invalid format");
        static IniLine _subject;
        static string x;
        static Exception _error;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_value : WithFakes
    {
        Establish context = () => _subject = new IniLine("entry = value");
        Because of = () => _entry = _subject.Value;
        It should_evaluate_entry = () => _entry.ShouldEqual("value");
        static IniLine _subject;
        static string _entry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_value_with_trailing_spaces_ : WithFakes
    {
        Establish context = () => _subject = new IniLine("          entry =          value");
        Because of = () => _entry = _subject.Value;
        It should_evaluate_entry_without_trailing_spaces = () => _entry.ShouldEqual("value");
        static IniLine _subject;
        static string _entry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_value_preserving_spaces_ : WithFakes
    {
        Establish context = () => _subject = new IniLine("entry = \"         value\"");
        Because of = () => _entry = _subject.Value;
        It should_evaluate_entry_without_trailing_spaces = () => _entry.ShouldEqual("         value");
        static IniLine _subject;
        static string _entry;
    }
}