using System;
using System.Drawing;
using System.Threading;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace FracMaster
{
    public class Generic2DFractal : GenericFractal
    {
        public Generic2DFractal()
        {
            pars.SetValue("X", 0.0);
            pars.SetValue("Y", 0.0);
            pars.SetValue("XC", 0.0);
            pars.SetValue("YC", 0.0);
            pars.SetValue("W", 1.0);
            pars.SetValue("H", 1.0);
            pars.SetValue("WIDTH", 640);
            pars.SetValue("HEIGHT", 480);
            pars.SetValue("VERSION", "1.0.0");
            pars.AddValue("ITERATIONS", 64);
            pars.AddValue("ZOOMABLE", 1);
            pars.AddValue("SCROLLABLE", 1);
            pars.AddValue("NUM_THREADS", Environment.ProcessorCount);
            pars.AddValue("APPLY_BILINEAR_FILTER", 0);            
        }

        virtual public void SetOrigin(double dx, double dy)
        {
             
            double CurWpix = (int)pars.GetValue("WIDTH");
            double CurHpix = (int)pars.GetValue("HEIGHT");
            double FracWidth = (double)pars.GetValue("W");
            double FracHeight = (double)pars.GetValue("H");
            double FracX = (double)pars.GetValue("X");
            double FracY = (double)pars.GetValue("Y");

            FracX -= dx * FracWidth / CurWpix;
            FracY -= dy * FracHeight / CurHpix;

            pars.SetValue("X", FracX);
            pars.SetValue("Y", FracY);
        }

        virtual public void SetControlParameter(double dx, double dy)
        {
            double CurWpix = (int)pars.GetValue("WIDTH");
            double CurHpix = (int)pars.GetValue("HEIGHT");
            double FracWidth = (double)pars.GetValue("W");
            double FracHeight = (double)pars.GetValue("H");
            double FracX = (double)pars.GetValue("XC");
            double FracY = (double)pars.GetValue("YC");

            FracX -= dx * FracWidth / CurWpix;
            FracY -= dy * FracHeight / CurHpix;

            pars.SetValue("XC", FracX);
            pars.SetValue("YC", FracY);
        }

        override protected void RenderFunction(object o)
        {
            object[] P = (object[])o;
            RenderResult.RenderComplete clbk = (RenderResult.RenderComplete)P[0];
            RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)P[1];

            try
            {
                Random r = new Random();

                int width = (int)pars.GetValue("WIDTH");
                int heigth = (int)pars.GetValue("HEIGHT");
                int iterations = (int)pars.GetValue("ITERATIONS") - 1;
                Int32[] Palette = (Int32[])pars.GetValue("PALETTE");
                int NumThreads = (int)pars.GetValue("NUM_THREADS", 2);
                int BilinearFilter = (int)pars.GetValue("APPLY_BILINEAR_FILTER",0);  

                int[] colrTable = new int[width * heigth];
                
                WaitHandle[] handles = new WaitHandle[NumThreads];
                Thread[] threads = new Thread[NumThreads];

                lines_rendered = 0;

                for (int i = 0; i < NumThreads; i++)
                {
                    handles[i] = new AutoResetEvent(false);
                    threads[i] = new Thread(new ParameterizedThreadStart(PartialRender));
                    threads[i].Start((object)(new object[] { i * heigth / NumThreads, 
                                                             heigth / NumThreads, 
                                                             colrTable, 
                                                             status_clbk, handles[i] }));
                }
 
                while (true)
                {
                    if (WaitHandle.WaitAll(handles, 100, false) == true)
                    {
                        break;
                    }
                    else if (interrupt.WaitOne(100, false) == true)
                    {
                        try
                        {
                            for (int i = 0; i < NumThreads; i++)
                            {
                                threads[i].Abort();
                            }
                        }
                        catch { }

                        clbk(null, -2);

                        return;
                    }
                }
                
                if (BilinearFilter == 1)
                {
                    int [] filteredColorTable =  new int[(width * heigth)];
                    int idxs11 = 0,idxs12 = 0,idxs21 = 0,idxs22 = 0;

                    for (int y = 0; y < heigth-1; y++)
                    {
                        idxs11 = y * (width);
                        idxs12 = idxs11 + 1;
                        idxs21 = idxs11 + width;
                        idxs22 = idxs21 + 1;

                        for (int x = 0; x < width-1; x++)
                        {                            
                            int colf1 = Utils.InterpolateColors(colrTable[idxs11], colrTable[idxs12], 127);
                            int colf2 = Utils.InterpolateColors(colrTable[idxs21], colrTable[idxs22], 127);
                            
                            filteredColorTable[idxs11] = Utils.InterpolateColors(colf1, colf2, 128);
                            
                            idxs11++;
                            idxs12++;
                            idxs21++;
                            idxs22++;
                        }
                    }
                   
                    colrTable = filteredColorTable;
                }

                Bitmap bmp = new Bitmap(width, heigth, PixelFormat.Format32bppPArgb);
                BitmapData pdate = bmp.LockBits(new Rectangle(0, 0, width, heigth),
                                                ImageLockMode.ReadWrite,
                                                PixelFormat.Format32bppPArgb);

                IntPtr pscan0 = pdate.Scan0;
               
                Marshal.Copy(colrTable, 0, pscan0, width * heigth);
 
                bmp.UnlockBits(pdate);

                res.IsCompleted = true;

                ((AutoResetEvent)(res.AsyncWaitHandle)).Set();
                
                clbk(bmp, 0);
            }
            catch
            {
                clbk(null, -1);
            }
        }

        virtual protected void PartialRender(object P)
        {

        }
    }

}
