using System;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniLine))]
    class When_line_contains_entry_but_starts_with_comment_sign
    {
        Establish context = () => _subject = new IniLine("; entry = value");
        Because of = () =>
            {
                _entryError = Catch.Exception(() => { var x = _subject.Entry; });
                _valueError = Catch.Exception(() => { var x = _subject.Value; });
                _isEntry = _subject.IsEntry;
            };
        It should_fail_for_entry = () => _entryError.ShouldBeOfType<InvalidOperationException>();
        It should_fail_for_value = () => _valueError.ShouldBeOfType<InvalidOperationException>();
        It should_not_see_entry = () => _isEntry.ShouldBeFalse();
        It should_fail_with_message = () => _entryError.Message.ShouldEqual("'; entry = value': entry has invalid format");
        static IniLine _subject;
        static Exception _entryError;
        static Exception _valueError;
        static bool _isEntry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_entry_but_starts_with_section_open_sign
    {
        Establish context = () => _subject = new IniLine("[ entry = value");
        Because of = () =>
            {
                _entryError = Catch.Exception(() => { var x = _subject.Entry; });
                _valueError = Catch.Exception(() => { var x = _subject.Value; });
                _isEntry = _subject.IsEntry;
            };
        It should_fail_for_entry = () => _entryError.ShouldBeOfType<InvalidOperationException>();
        It should_fail_for_value = () => _valueError.ShouldBeOfType<InvalidOperationException>();
        It should_not_see_entry = () => _isEntry.ShouldBeFalse();
        It should_fail_with_message = () => _entryError.Message.ShouldEqual("'[ entry = value': entry has invalid format");
        static IniLine _subject;
        static Exception _entryError;
        static Exception _valueError;
        static bool _isEntry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_entry_but_starts_with_section_close_sign
    {
        Establish context = () => _subject = new IniLine("] entry = value");
        Because of = () =>
            {
                _entryError = Catch.Exception(() => { var x = _subject.Entry; });
                _valueError = Catch.Exception(() => { var x = _subject.Value; });
                _isEntry = _subject.IsEntry;
            };
        It should_fail_for_entry = () => _entryError.ShouldBeOfType<InvalidOperationException>();
        It should_fail_for_value = () => _valueError.ShouldBeOfType<InvalidOperationException>();
        It should_not_see_entry = () => _isEntry.ShouldBeFalse();
        It should_fail_with_message = () => _entryError.Message.ShouldEqual("'] entry = value': entry has invalid format");
        static IniLine _subject;
        static Exception _entryError;
        static Exception _valueError;
        static bool _isEntry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_entry_without_attribute
    {
        Establish context = () => _subject = new IniLine("    = value");
        Because of = () =>
            {
                _entry = _subject.Entry;
                _value = _subject.Value;
            };
        It should_not_see_entry = () => _subject.IsEntry.ShouldBeFalse();
        It should_evaluate_entry_as_empty = () => _entry.ShouldBeEmpty();
        It should_evaluate_value_as_empty = () => _value.ShouldEqual("value");
        static IniLine _subject;
        static string _entry;
        static string _value;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_entry_without_value : WithFakes
    {
        Establish context = () => _subject = new IniLine("  entry =");
        Because of = () =>
            {
                _entry = _subject.Entry;
                _value = _subject.Value;
            };
        It should_see_entry = () => _subject.IsEntry.ShouldBeTrue();
        It should_evaluate_entry = () => _entry.ShouldEqual("entry");
        It should_evaluate_value_as_empty = () => _value.ShouldBeEmpty();
        static IniLine _subject;
        static string _entry;
        static string _value;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_entry : WithFakes
    {
        Establish context = () => _subject = new IniLine("entry = value");
        Because of = () => _entry = _subject.Entry;
        It should_see_entry = () => _subject.IsEntry.ShouldBeTrue();
        It should_evaluate_entry = () => _entry.ShouldEqual("entry");
        static IniLine _subject;
        static string _entry;
    }

    [Subject(typeof(IniLine))]
    class When_line_contains_regular_entry_with_trailing_spaces_ : WithFakes
    {
        Establish context = () => _subject = new IniLine("          entry = value");
        Because of = () => _entry = _subject.Entry;
        It should_see_entry = () => _subject.IsEntry.ShouldBeTrue();
        It should_evaluate_entry_without_trailing_spaces = () => _entry.ShouldEqual("entry");
        static IniLine _subject;
        static string _entry;
    }
}