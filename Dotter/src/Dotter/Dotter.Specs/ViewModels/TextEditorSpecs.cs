using Dotter.Core;
using Dotter.Core.ViewModels;
using Machine.Specifications;
using Prism.Events;
using It = Machine.Specifications.It;

namespace Dotter.Specs.ViewModels
{
    public static class FizzBuzzer
    {
        public static string Calculcate(int number)
        {
            var dividebleByThree = number % 3 == 0;
            var dividebleByFive = number % 5 == 0;

            if (dividebleByThree && dividebleByFive)
                return "FizzBuzz";
            if (dividebleByThree)
                return "Fizz";
            if (dividebleByFive)
                return "Buzz";

            return number.ToString();
        }
    }

    //[Subject(typeof(FizzBuzzer), "Fizzme")]
    //public class FizzBuzzerSpec : Spec
    //{
    //    int Number;

    //    FizzBuzzerSpec() // ctor
    //    {
    //        Specify (x => FizzBuzzer.Calculcate (Number))
    //            .Case ("Dividable by 3", _ => _
    //                .Given ("Number is 3", x => Number = 3)
    //                .It ("returns Fizz", x => x.Result.Should ().Be ("Fizz")));
    //    }
    //}

        //[Subject(typeof (TextEditorViewModel), "Initialize")]
        //public class When_texteditor_is_initialized : Spec<TextEditorViewModel>
        //{
        //    When_texteditor_is_initialized()
        //    {
        //        Specify (_ => _)

        //            .DefaultCase (_ => _
        //                .It ("should have no input", x => x.Result.Input.Should ().BeEmpty ()));
        //    }

    [Subject(typeof (TextEditorViewModel), "Initialize")]
    public class When_texteditor_is_initialized
    {

        Establish context = () =>
        {
            _eventAggregator = new EventAggregator();
        };

        Because of = () =>
        {
            _sut = new TextEditorViewModel(_eventAggregator);
        };

        It should_have_no_input = () => _sut.Input.ShouldBeEmpty();
        It should_have_current_filename = () => _sut.CurrentFileName.ShouldBeEmpty();


        static EventAggregator _eventAggregator;
        static TextEditorViewModel _sut;
    }

    /*
    [Subject(typeof (TextEditorViewModel))]
    internal class When_texteditor_is_initialized
    {
        Establish context = () =>
        {
            _eventAggregator = new Mock<IEventAggregator>();
        };

        Because of = () =>
        {
            _sut = new TextEditorViewModel(_eventAggregator.Object);
        };

        It should_have_no_input = () => _sut.Input.ShouldBeEmpty();
        It should_have_current_filename = () => _sut.CurrentFileName.ShouldBeEmpty();


        static Mock<IEventAggregator> _eventAggregator;
        static TextEditorViewModel _sut;
    }


    [Subject(typeof (TextEditorViewModel))]
    internal class When_loaded_was_published
    {
        Establish context = () =>
        {
            _eventAggregator = new Mock<IEventAggregator>();
            _sut = new TextEditorViewModel(_eventAggregator.Object);
            _statusbarEvent = new Mock<StatusbarMessageEvent>();
            _eventAggregator.Setup(x => x.GetEvent<StatusbarMessageEvent>()).Returns(_statusbarEvent.Object);
            _fileLoadedEvent = new Mock<FileLoadedEvent>();
            _eventAggregator.Setup(x => x.GetEvent<FileLoadedEvent>()).Returns(_fileLoadedEvent.Object);
        };

        Because of = () =>
        {
            _sut.OnLoadFile(@"data\SimpleGraph");
        };

        It should_publish_statusbar_event = () => _statusbarEvent.Verify(x => x.Publish(Moq.It.IsAny<string>()));
        It should_publish_fileloaded_event = () => _fileLoadedEvent.Verify(x => x.Publish(Moq.It.IsAny<string>()));

        static Mock<IEventAggregator> _eventAggregator;
        static TextEditorViewModel _sut;
        static Mock<StatusbarMessageEvent> _statusbarEvent;
        static Mock<FileLoadedEvent> _fileLoadedEvent;
    }
    */
}
