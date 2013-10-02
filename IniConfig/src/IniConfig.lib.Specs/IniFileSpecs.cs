using System;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.lib.Specs
{
    [Subject(typeof(IniFile))]
    internal class When_loading_not_existing_inifile : WithFakes
    {
        Because of = () => _error = Catch.Exception(() => IniFile.LoadFrom("NotExisting"));

        It should_fail_with_exception = () => _error.ShouldBeOfType(typeof(AggregateException));

        static object _error;
    }
}