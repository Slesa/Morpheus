using IniConfig.Editor.lib;
using IniConfig.Editor.lib.ViewModels;
using Machine.Fakes;
using Machine.Specifications;
using Microsoft.Practices.Prism.Events;

namespace IniConfig.Editor.specs.ViewModels
{
    [Subject(typeof(StatusBarViewModel))]
    class When_creating_statusbar_viewmodel : StatusBarViewModelSpecBase
    {
        It should_have_no_message = () => Subject.Message.ShouldBeNull();
    }


    [Subject(typeof(StatusBarViewModel))]
    class When_raising_show_status_message_event : StatusBarViewModelSpecBase
    {
        Because of = () => EventAggregator.GetEvent<ShowStatusMessageEvent>().Publish(Message);

        It should_have_message = () => Subject.Message.ShouldEqual(Message);

        const string Message = "A message";
    }



    [Subject(typeof(StatusBarViewModel))]
    internal class StatusBarViewModelSpecBase : WithFakes
    {
        Establish context = () =>
            {
                EventAggregator = new EventAggregator();
                Subject = new StatusBarViewModel(EventAggregator);
            };

        protected static EventAggregator EventAggregator;
        protected static StatusBarViewModel Subject;
    }
}