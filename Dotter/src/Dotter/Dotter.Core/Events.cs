using Prism.Events;

namespace Dotter.Core
{
    public class StatusbarMessageEvent : PubSubEvent<string> {}
    public class TextInputUpdatedEvent : PubSubEvent<string> { }
    public class ClearTextInputEvent : PubSubEvent<int> { }
    public class LoadFileEvent : PubSubEvent<string> { }
    public class SaveFileEvent : PubSubEvent<int> { }
    public class FileSavedEvent : PubSubEvent<string> { }
    public class FileLoadedEvent : PubSubEvent<string> { }
}