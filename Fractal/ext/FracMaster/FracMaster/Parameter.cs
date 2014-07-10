using System;
using System.Collections.Generic;
using System.Text;

namespace FracMaster
{
    public class Parameter
    {
        private String name = String.Empty;
        private object value = null;

        public Parameter(String name, object value)
        {
            this.name = name;
            this.value = value;
        }

        public String Name
        {
            get { return name; }
        }

        public object Value
        {
            get { return value; }
            set { this.value = value; }
        }

        public Type Type
        {
            get { return this.value.GetType(); }
        }
    }

}
