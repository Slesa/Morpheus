using System;
using System.Collections.Generic;
using System.Collections;
 
namespace FracMaster
{
    
    public class ParameterSet : IFractalParameters
    {

        private readonly List<Parameter> _pars = new List<Parameter>();
       
        public IEnumerator GetEnumerator()
        {
            return _pars.GetEnumerator(); 
        }
        
        public object Clone()
        {
            var p = new ParameterSet();            
            foreach(var px in _pars)
            {
                p.AddValue(px.Name,px.Value);
            }
            return p;            
        }

        public object Current 
        {
            get
            {
                return _pars.GetEnumerator().Current;
            }
        }

        public bool MoveNext()
        {
            return _pars.GetEnumerator().MoveNext();
        }

        public void Reset()
        {
             
        }

        public bool HasValue(String name)
        {
            foreach (var p in _pars)
            {
                if (p.Name == name)
                {                    
                    return true;
                }
            }
            return false;
        }

        public void SetValue(String name, object value)
        {
            foreach (var p in _pars)
            {
                if (p.Name == name)
                {
                      p.Value = value;
                      return;
                }
            }
            AddValue(name, value);            
        }

        public object GetValue(String name)
        {
            foreach (var p in _pars)
            {
                if (p.Name == name)
                {
                    return p.Value;
                }
            }
            throw new ApplicationException("parameter '" + name + "' not found");
        }

        public object GetValue(String name, object defaultValue)
        {
            foreach (var p in _pars)
            {
                if (p.Name == name)
                {
                    return p.Value;
                }
            }
            return defaultValue;
        }

        public void AddValue(String name, object value)
        {
            foreach (var p in _pars)
            {
                if (p.Name == name)
                {
                    throw new ArgumentException("Paramter with that name already exists");
                }
            }

            _pars.Add(new Parameter(name, value));
        }
    }
}
