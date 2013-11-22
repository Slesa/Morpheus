using System;
using IniConfig.lib;
using Microsoft.Practices.Prism.ViewModel;

namespace IniConfig.Editor.lib.Models
{
    public class Document : NotificationObject
    {
        Document(string filePath, IniFile iniFile)
        {
            _filePath = filePath;
            IniFile = iniFile;
        }

        public static Document CreateDocument(string filePath)
        {
            try
            {
                var iniFile = IniFile.LoadFrom(filePath);
                var document = new Document(filePath, iniFile);
                return document;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        string _filePath;
        public string FilePath
        {
            get { return _filePath; }
            set
            {
                IniFile.Save(value);
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

        public IniFile IniFile { get; private set; }
    }
}