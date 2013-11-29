using IniConfig.lib;
using Microsoft.Practices.Prism.ViewModel;

namespace IniConfig.Editor.lib.ViewModels
{
    public class IniEntryViewModel : NotificationObject
    {
        readonly IniEntry _entry;

        public IniEntryViewModel(IniEntry entry)
        {
            _entry = entry;
        }

        public string EntryName
        {
            get { return _entry.Attribute; }
            set
            {
                _entry.Attribute = value;
                RaisePropertyChanged(() => EntryName);
            }
        }

        public string EntryValue
        {
            get { return _entry.Value; }
            set
            {
                _entry.Value = value;
                RaisePropertyChanged(() => EntryValue);
            }
        }

    }
}