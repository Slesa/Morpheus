using System;

namespace FracMaster
{
    public class Parameter
    {
        public Parameter(string name, object value)
        {
            Name = name;
            Value = value;
        }

        public string Name { get; private set; }
        public object Value { get; set; }

        public Type Type
        {
            get { return Value.GetType(); }
        }
    }

}
