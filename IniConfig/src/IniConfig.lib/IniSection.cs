using System.Collections.Generic;

namespace IniConfig.lib
{
    public class IniSection
    {
        public string Name { get; set; }

        List<string> _remarks;
        public List<string> Remarks
        {
            get { return _remarks ?? (_remarks = new List<string>()); }
        }

        List<IniElement> _elements;
        public List<IniElement> Elements
        {
            get { return _elements ?? (_elements = new List<IniElement>()); }
        }
    }
}