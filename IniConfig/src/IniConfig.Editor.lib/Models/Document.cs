using IniConfig.lib;
using Microsoft.Practices.Prism.ViewModel;

namespace IniConfig.Editor.lib.Models
{
    public class Document : NotificationObject
    {
        IniFile _iniFile;

        public Document(string filePath)
        {
            _filePath = filePath;
            _iniFile = IniFile.LoadFrom(filePath);
        }

string _filePath;
        public string FilePath
        {
            get { return _filePath; }
            set
            {
                _filePath = value;
                RaisePropertyChanged(() => FilePath);
            }
        }

        bool _hasChanged;
        public bool HasChanged
        {
            get { return _hasChanged; }
            set
            {
                _hasChanged = value;
                RaisePropertyChanged(() => HasChanged);
            }
        }
    }
}