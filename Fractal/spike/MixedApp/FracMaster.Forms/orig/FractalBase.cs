using System;
using System.IO;
using System.Text;
using System.Threading;
using System.Drawing;
using System.Xml;

namespace FracMaster
{
    
    public class GenericFractal : IFractal 
    {
        
        protected RenderResult res = null;
        protected IFractalParameters pars = new ParameterSet();
        protected AutoResetEvent interrupt = new AutoResetEvent(false);
        protected int lines_rendered = 0;

        public GenericFractal()
        {
            // basic parameters that any fractal should use:
            // name of the fractal
            pars.AddValue("NAME", "GenericFractal");
            // output width and height
            pars.AddValue("WIDTH", 800);
            pars.AddValue("HEIGHT", 600);
            // version of the fractal render engine 
            pars.AddValue("VERSION", "1.0.0");
           
            int Colors = 256;

            Int32[] Palette = new Int32[Colors];

            for (int i = 0; i < Colors; i++)
            {
                int g = (int)(255.0 * (double)i / (double)Colors);
                Palette[i] = Color.FromArgb(g, g, g).ToArgb();
            }

            Palette[Colors - 1] = Palette[0];
             
            pars.AddValue("PALETTE", Palette);

        }


      

        public void ReadFromXml(Stream instream)
        {
            try
            {

                XmlDocument xmldoc = new XmlDocument();
                xmldoc.Load(instream);
                XmlNodeList nodes = xmldoc.GetElementsByTagName("frac");
                if (nodes.Count == 1)
                {
                    nodes = xmldoc.GetElementsByTagName("parameter");
                    foreach (XmlNode n in nodes)
                    {
                        String type = n.Attributes["type"].Value;
                        String name = n.Attributes["name"].Value;
                        String value = n.InnerXml;

                        if (type == "System.Int32[]")
                        {
                            String[] vals = value.Split(new char[] { ',' });
                            int Count = vals.Length;
                            Int32[] values = new Int32[Count];
                            for (int i = 0; i < Count; i++)
                            {
                                values[i] = Convert.ToInt32(vals[i]);
                            }
                            pars.SetValue(name, values);
                        }
                        else if (type == "System.Int32")
                        {
                            pars.SetValue(name, Convert.ToInt32(value));
                        }
                        else if (type == "System.Double")
                        {
                            pars.SetValue(name, Convert.ToDouble(value));
                        }
                        else if (type == "System.String")
                        {
                            pars.SetValue(name, value);
                        }
                        else
                        {
                            throw new ApplicationException("unsupported parameter type:" + type);
                        }
                    }
                }
                else
                {
                    throw new IOException("illegal file format!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("exception caught: " + ex.Message);
            }
        }

        virtual  public void ReadFromXml(String filename)
        {
           // 
            try
            {
                FileStream f = new FileStream(filename, FileMode.Open);
                ReadFromXml(f);               
            }
            catch
            {

            }
        }

        virtual public void WriteToXml(String filename )
        {
            try
            {
                Stream stream = File.Open(filename, FileMode.Create);

                String name = (String)this.pars.GetValue("NAME");

                TextWriter w = new StreamWriter(stream, Encoding.UTF8);
                w.WriteLine("<?xml version='1.0' encoding='utf-8' ?>");
                w.WriteLine("<frac name='" + name + "' type='"+this.GetType().ToString()+"'>");

                foreach (Parameter p in Parameters)
                {
                    String pname = p.Name;
                    String type = p.Type.ToString();

                    if (type == "System.Int32[]")
                    {
                        Int32[] pal = (Int32[])p.Value;                                                 
                        String palette = String.Empty;

                        for (int i=0;i<pal.Length;i++)
                        {
                            // TODO : format to hex
                            if (i < pal.Length - 1) palette += ""+pal[i] + ",";                        
                            else palette += "" + pal[i]  ;                             
                        }

                        w.WriteLine("<parameter name='"+pname+"' type='" + type + "' >" + palette + "</parameter>");
                    }
                    else if (type == "System.Int32" ||
                             type == "System.String" || 
                             type == "System.Double" || 
                             type == "System.Float")
                    {
                        String value = p.Value.ToString();
                        w.WriteLine("<parameter name='" + pname + "' type='" + type + "' >" + value + "</parameter>");
                    }
                    else
                    {
                        throw new ApplicationException("unsupported parameter type:" + type);
                    }
                }

                w.WriteLine("</frac>");
                w.Flush();
                w.Close();
            }
            catch
            {
            }
        }

         

        public IFractalParameters Parameters
        {
            get
            {
                return pars;
            }
            set
            {
                pars = value;
            }
        }

        public IAsyncResult BeginRender(Delegate completed, Delegate status)
        {
            if (res == null)
            {
                res = new RenderResult();
                interrupt.Reset();
                Thread d = new Thread(new ParameterizedThreadStart(RenderFunction));
                d.Start(new object[] { completed, status });
                res.AsyncState = d;
                return res;
            }
            else
            {
                throw new ApplicationException("BeginRender already called");
            }
        }

        public void EndRender(IAsyncResult Res)
        {
            interrupt.Set();
            res = null;
        }
         
        virtual protected void RenderFunction(object o)
        {
            throw new ApplicationException("Virtual function not overridden!");
        }

        virtual public void Configure()
        {
            FractalSettingsDialog dia = new FractalSettingsDialog();
            dia.Parameters = (IFractalParameters)this.Parameters.Clone();
            if (dia.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Parameters = dia.Parameters;
            }
        }
    }

}
