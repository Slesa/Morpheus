using Dotter.Core;
using Dotter.Core.ViewModels;
using Machine.Specifications;
using Moq;
using Prism.Events;
using It = Machine.Specifications.It;

namespace Dotter.Specs.ViewModels
{
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
}