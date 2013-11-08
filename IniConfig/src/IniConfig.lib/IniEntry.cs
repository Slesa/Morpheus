using System.Collections.Generic;
using System.Globalization;

namespace IniConfig.lib
{
    /// <summary>
    /// The attribute/value pair representation of a configuration line, a so called entry.
    /// </summary>
    public class IniEntry
    {
        readonly IniLine _iniLine;

        /// <summary>
        /// Create a configuration entry, based on a configuration line.
        /// </summary>
        /// <param name="iniLine">The configuration line of the entry</param>
        public IniEntry(IniLine iniLine)
        {
            _iniLine = iniLine;
        }

        public IEnumerable<IniLine> Lines
        {
            get { yield return _iniLine; }
        }

        /// <summary>
        /// The attribute of the configuration entry, means the name before the equal sign.
        /// </summary>
        public string Attribute
        {
            get { return _iniLine.Entry; }
            set { _iniLine.Entry = value; }
        }

        /// <summary>
        /// The value of the configuration entry, means the value after the equals sign
        /// </summary>
        public string Value
        {
            get { return _iniLine.Value; }
            set { _iniLine.Value = value; }
        }

        /// <summary>
        /// True, if the entry's value is a bool.
        /// </summary>
        public bool IsBool
        {
            get
            {
                bool tmp;
                return bool.TryParse(Value, out tmp);
            }
        }

        /// <summary>
        /// The boolean value of the entry, if it can be parsed as bool. Always false otherwise.
        /// </summary>
        public bool AsBool
        {
            get
            {
                bool result;
                return bool.TryParse(Value, out result) ? result : false;
            }
            set { Value = value.ToString(); }
        }

        /// <summary>
        /// True, if the entry's value is an int.
        /// </summary>
        public bool IsInt
        {
            get
            {
                int tmp;
                return int.TryParse(Value, out tmp);
            }
        }

        /// <summary>
        /// The integer value of the entry, if it can be parsed as int. Always 0 otherwise.
        /// </summary>
        public int AsInt
        {
            get
            {
                int result;
                return int.TryParse(Value, out result) ? result : 0;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        /// <summary>
        /// True, if the entry's value is a double.
        /// </summary>
        public bool IsDouble
        {
            get
            {
                double tmp;
                return double.TryParse(Value, out tmp);
            }
        }

        /// <summary>
        /// The double value of the entry, if it can be parsed as double. Always 0 otherwise. Note, that it is stored as InvariantCulture, means xx.yy.
        /// </summary>
        public double AsDouble
        {
            get
            {
                double result;
                return double.TryParse(Value, NumberStyles.Any, CultureInfo.InvariantCulture, out result) ? result : 0.0;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        /// <summary>
        /// True, if the entry's value is a decimal.
        /// </summary>
        public bool IsDecimal
        {
            get
            {
                decimal tmp;
                return decimal.TryParse(Value, out tmp);
            }
        }

        /// <summary>
        /// The decimal value of the entry, if it can be parsed as decimal. Always 0 otherwise. Note, that it is stored as InvariantCulture, means xx.yy.
        /// </summary>
        public decimal AsDecimal
        {
            get
            {
                decimal result;
                return decimal.TryParse(Value, NumberStyles.Any, CultureInfo.InvariantCulture, out result) ? result : 0.0m;
            }
            set { Value = value.ToString(CultureInfo.InvariantCulture); }
        }

        /// <summary>
        /// The value interpreted as string list, with a semicolon as seperator.
        /// </summary>
        public IEnumerable<string> AsStringList
        {
            get { return Value.Split(';'); } set { Value = string.Join(";", value); }
        }
    }
}