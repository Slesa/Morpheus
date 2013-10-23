using System.Collections.ObjectModel;

namespace IniConfig.Editor.lib.DesignTime
{
    public class DesignDocumentViewModel
    {
        public DesignDocumentViewModel()
        {
            Sections = new ObservableCollection<string>()
                {
                    "Log",
                    "Devices",
                };
            SectionEntries = new ObservableCollection<string>()
                {
                    "Level",
                    "MaxSize",
                };
        }
    
        public ObservableCollection<string> Sections { get; set; } 
        public ObservableCollection<string> SectionEntries { get; set; } 

    }
}