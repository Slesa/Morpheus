using System;
using System.Drawing;
using System.Threading;

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
            var p = (object[])o;
            var clbk = (RenderResult.RenderComplete)p[0];
            var statusClbk = (RenderResult.RenderStatus)p[1];

            try
            {
                               
                var width = (int)pars.GetValue("WIDTH");
                var heigth = (int)pars.GetValue("HEIGHT");

                var bmp = new Bitmap(width, heigth, System.Drawing.Imaging.PixelFormat.Format32bppPArgb);

                using (var g = Graphics.FromImage(bmp))
                {
                    var r = new Random();

                    for (var i = 0; i < 10000; i++)
                    {
                        var x = r.Next(0, width);
                        var y = r.Next(0, heigth);
                        var w = r.Next(1, width - x);
                        var h = r.Next(1, heigth - y);
                        var col = r.Next(0, 255);
                        using (var br = new SolidBrush(Color.FromArgb(col, col, col)))
                        {
                            g.FillRectangle(br, new Rectangle(x, y, w, h));
                        }
                        statusClbk(i / 100.0f);
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
