using IniConfig.Editor.lib.Models;
using Microsoft.Practices.Prism.Events;

namespace IniConfig.Editor.lib
{
    public class DocumentChangedEventEvent : CompositePresentationEvent<Document> { }

    public class ShowStatusMessageEvent : CompositePresentationEvent<string> { }
}