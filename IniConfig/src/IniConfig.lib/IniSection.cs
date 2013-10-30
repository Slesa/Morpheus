using System.Collections.Generic;
using System.Linq;

namespace IniConfig.lib
{
    public class IniSection
    {
        public static IniSection CreateSection(string name)
        {
            return new IniSection {Name = name};
        }

        public string Name { get; set; }

        List<string> _remarks;
        public List<string> Remarks
        {
            get { return _remarks ?? (_remarks = new List<string>()); }
        }

        public IniSection AddRemark(string remark)
        {
            Remarks.Add(remark);
            return this;
        }

        List<IniElement> _elements;
        public IEnumerable<IniElement> Elements
        {
            get { return _elements ?? (_elements = new List<IniElement>()); }
        }

        public IniElement FindElement(string name)
        {
            return Elements.FirstOrDefault(s => s.Attribute.ToLower().Equals(name.ToLower()));
        }

        public void AddElement(string attribute, string value)
        {
            var element = FindElement(attribute);
            if (element != null)
                element.Value = value;
            else
                ((List<IniElement>)Elements).Add(new IniElement(attribute, value));
        }
    }
}