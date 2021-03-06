﻿using System.Collections.Generic;
using System.Linq;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    #region Boolean

    [Subject(typeof (IniEntry))]
    class When_setting_ini_entry_to_bool_for_true : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsBool = true;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("True");
        static string _value;
    }

    [Subject(typeof (IniEntry))]
    class When_setting_ini_entry_to_bool_for_false : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsBool = false;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("False");
        static string _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_bool_for_true : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "TRUe";
        Because of = () => _value = Subject.AsBool;
        It should_mark_as_bool = () => Subject.IsBool.ShouldBeTrue();
        It should_return_true = () => _value.ShouldBeTrue();
        static bool _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_bool_for_false : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "False";
        Because of = () => _value = Subject.AsBool;
        It should_mark_as_bool = () => Subject.IsBool.ShouldBeTrue();
        It should_return_false = () => _value.ShouldBeFalse();
        static bool _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_bool_for_garbage : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "garbage";
        Because of = () => _value = Subject.AsBool;
        It should_not_mark_as_bool = () => Subject.IsBool.ShouldBeFalse();
        It should_return_false = () => _value.ShouldBeFalse();
        static bool _value;
    }

    #endregion

    #region Integer

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_int_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsInt = 42;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("42");
        static string _value;
    }

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_int_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsInt = -42;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("-42");
        static string _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_int_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "42";
        Because of = () => _value = Subject.AsInt;
        It should_mark_as_int = () => Subject.IsInt.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(42);
        static int _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_int_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "-42";
        Because of = () => _value = Subject.AsInt;
        It should_mark_as_int = () => Subject.IsInt.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(-42);
        static int _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_int_for_garbage : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "garbage";
        Because of = () => _value = Subject.AsInt;
        It should_not_mark_as_int = () => Subject.IsInt.ShouldBeFalse();
        It should_return_zero = () => _value.ShouldEqual(0);
        static int _value;
    }

    [Subject(typeof(IniEntry))]
    class When_reading_ini_entry_as_int_for_double : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "42.3";
        Because of = () => _value = Subject.AsInt;
        It should_return_value = () => _value.ShouldEqual(0);
        static int _value;
    }

    #endregion

    #region Double

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_double_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsDouble = 42.42;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("42.42");
        static string _value;
    }

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_double_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsDouble = -42.42;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("-42.42");
        static string _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_double_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "42.42";
        Because of = () => _value = Subject.AsDouble;
        It should_mark_as_double = () => Subject.IsDouble.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(42.42);
        static double _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_double_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "-42.42";
        Because of = () => _value = Subject.AsDouble;
        It should_mark_as_double = () => Subject.IsDouble.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(-42.42);
        static double _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_double_for_garbage : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "garbage";
        Because of = () => _value = Subject.AsDouble;
        It should_not_mark_as_double = () => Subject.IsDouble.ShouldBeFalse();
        It should_return_zero = () => _value.ShouldEqual(0.0);
        static double _value;
    }

    #endregion

    #region Decimal

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_decimal_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsDecimal = 42.42m;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("42.42");
        static string _value;
    }

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_decimal_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsDecimal = -42.42m;
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("-42.42");
        static string _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_decimal_for_positive : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "42.42";
        Because of = () => _value = Subject.AsDecimal;
        It should_mark_as_decimal = () => Subject.IsDecimal.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(42.42m);
        static decimal _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_decimal_for_negative : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "-42.42";
        Because of = () => _value = Subject.AsDecimal;
        It should_mark_as_decimal = () => Subject.IsDecimal.ShouldBeTrue();
        It should_return_value = () => _value.ShouldEqual(-42.42m);
        static decimal _value;
    }

    [Subject(typeof (IniEntry))]
    class When_reading_ini_entry_as_decimal_for_garbage : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "garbage";
        Because of = () => _value = Subject.AsDecimal;
        It should_not_mark_as_decimal = () => Subject.IsDecimal.ShouldBeFalse();
        It should_return_zero = () => _value.ShouldEqual(0.0m);
        static decimal _value;
    }

    #endregion

    #region StringList

    [Subject(typeof(IniEntry))]
    class When_setting_ini_entry_to_stringlist : WithSubject<IniEntry>
    {
        Establish context = () => Subject.AsStringList = new List<string> {"Dark Red", "Green", "Blue"};
        Because of = () => _value = Subject.Value;
        It should_return_true = () => _value.ShouldEqual("Dark Red;Green;Blue");
        static string _value;
    }

    [Subject(typeof(IniEntry))]
    class When_reading_ini_entry_as_stringlist : WithSubject<IniEntry>
    {
        Establish context = () => Subject.Value = "Dark Red;Green;Blue";
        Because of = () => _value = Subject.AsStringList;
        It should_return_true = () => _value.Count().ShouldEqual(3);
        static IEnumerable<string> _value;
    }

    #endregion
}