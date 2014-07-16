using System;
using System.Collections;

namespace FracMaster
{
    public interface IFractalParameters :  IEnumerable,  IEnumerator, ICloneable
    {
        bool HasValue(String name);
        void AddValue(String name, object value);
        void SetValue(String name, object value);
        object GetValue(String name);
        object GetValue(String name, object defaultValue);
    }
}
