using System.Collections.Generic;
using System.Globalization;

namespace IniConfig.lib
{
    public class IniEntry
    {
        public IniEntry(string entry, string value)
        {
            Attribute = entry;
            Value = value;
        }

        public string Attribute { get; set; }
        public string Value { get; set; }

        public bool IsBool
        {
            get
            {
                bool tmp;
                return bool.TryParse(Value, out tmp);
            }
        }

        public bool AsBool
        {
            get
            {
                bool result;
                return bool.TryParse(Value, out result) ? result : false;
            }
            set { Value = value.ToString(); }
        }

        public bool IsInt
        {
            get
            {
                int tmp;
                return int.TryParse(Value, out tmp);
            }
        }

        public int AsInt
        {
            get
            {
                int result;
                return int.TryParse(Value, out result) ? result : 0;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        public bool IsDouble
        {
            get
            {
                double tmp;
                return double.TryParse(Value, out tmp);
            }
        }

        public double AsDouble
        {
            get
            {
                double result;
                return double.TryParse(Value, NumberStyles.Any, CultureInfo.InvariantCulture, out result) ? result : 0.0;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        public bool IsDecimal
        {
            get
            {
                decimal tmp;
                return decimal.TryParse(Value, out tmp);
            }
        }

        public decimal AsDecimal
        {
            get
            {
                decimal result;
                return decimal.TryParse(Value, NumberStyles.Any, CultureInfo.InvariantCulture, out result) ? result : 0.0m;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        public IEnumerable<string> AsStringList
        {
            get { return Value.Split(';'); } set { Value = string.Join(";", value); }
        }
    }
}