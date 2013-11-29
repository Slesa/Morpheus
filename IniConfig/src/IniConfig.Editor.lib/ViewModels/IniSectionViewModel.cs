using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using IniConfig.lib;
using Microsoft.Practices.Prism;
using Microsoft.Practices.Prism.ViewModel;

namespace IniConfig.Editor.lib.ViewModels
{
    public class IniSectionViewModel : NotificationObject
    {
        readonly IniSection _section;

        public IniSectionViewModel(IniSection section)
        {
            _section = section;
            Entries = new ObservableCollection<IniEntryViewModel>();
            Entries.AddRange(_section.Entries.Select(x => new IniEntryViewModel(x)));
        }


        public string SectionName
        {
            get { return _section.Name; }
            set
            {
                _section.Name = value;
                RaisePropertyChanged(() => SectionName);
            }
        }

        public IEnumerable<string> Remarks
        {
            get { return _section.Remarks; }
            set
            {
                //_section.Rem = value;
                RaisePropertyChanged(() => Remarks);
            }
        }

        public ObservableCollection<IniEntryViewModel> Entries { get; private set; }
    }
}