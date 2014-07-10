using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Runtime.Serialization;

namespace FracMaster
{
  
  
    public class TestFractal : GenericFractal 
    {                          
        public TestFractal()
        {
            pars.SetValue("NAME", "Render Test");                     
        }        

        override protected void RenderFunction(object o)
        {
            object[] P = (object[])o;
            RenderResult.RenderComplete clbk = (RenderResult.RenderComplete)P[0];
            RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)P[1];

            try
            {
                               
                int width = (int)pars.GetValue("WIDTH");
                int heigth = (int)pars.GetValue("HEIGHT");

                Bitmap bmp = new Bitmap(width, heigth, System.Drawing.Imaging.PixelFormat.Format32bppPArgb);

                using (Graphics g = Graphics.FromImage(bmp))
                {
                    Random r = new Random();

                    for (int i = 0; i < 10000; i++)
                    {
                        int x = r.Next(0, width);
                        int y = r.Next(0, heigth);
                        int w = r.Next(1, width - x);
                        int h = r.Next(1, heigth - y);
                        int col = r.Next(0, 255);
                        using (SolidBrush br = new SolidBrush(Color.FromArgb(col, col, col)))
                        {
                            g.FillRectangle(br, new Rectangle(x, y, w, h));
                        }
                        status_clbk(((float)i) / 100.0f);
                    }
                }

                res.IsCompleted = true;
                ((AutoResetEvent)(res.AsyncWaitHandle)).Set();
                clbk(bmp, 0);
            }
            catch
            {
                clbk(null, -1);
            }
        }

       

         
    }
}
