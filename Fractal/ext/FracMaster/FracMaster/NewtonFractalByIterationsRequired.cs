using System;
using System.Threading;

namespace FracMaster
{
    public class NewtonFractalByIterationsRequired : Generic2DFractal
    {
        public NewtonFractalByIterationsRequired()
        {
            pars.SetValue("NAME", "Newton Fractal by iterations required");
            pars.SetValue("X",0.0);
            pars.SetValue("Y", 0.0);
            pars.SetValue("W", 8.0);
            pars.SetValue("H", 8.0);
            pars.SetValue("A", 1.0);
            pars.SetValue("WIDTH", 800);
            pars.SetValue("HEIGHT", 800);
            pars.SetValue("VERSION", "1.0.0");
            pars.SetValue("ITERATIONS", 32);
            pars.SetValue("NUM_THREADS", Environment.ProcessorCount);
            Int32[] pal = { -16777088, -15662976, -14548864, -13434752, -12320640, -11206528, -10092416, -8978304, -7864192, -6750080, -5635968, -4521856, -3407744, -2293632, -1179520, -65408, -61576, -57488, -53400, -49312, -45224, -41136, -37048, -32960, -28872, -24784, -20696, -16608, -12520, -8432, -4344, -256, -12713984, -12318712, -11923440, -11528168, -11132896, -10671831, -10276559, -9881287, -9486015, -9024950, -8629678, -8234406, -7839134, -7443862, -6982797, -6587525, -6192253, -5796981, -5335916, -4940644, -4545372, -4150100, -3754828, -3293763, -2898491, -2503219, -2107947, -1646882, -1251610, -856338, -461066, -1, -16760832, -16235000, -15709168, -15183336, -14657504, -14066135, -13540303, -13014215, -12488383, -11897014, -11371182, -10845350, -10319518, -9793430, -9202061, -8676229, -8150397, -7624565, -7033196, -6507108, -5981276, -5455444, -4929612, -4338243, -3812411, -3286323, -2760491, -2169122, -1643290, -1117458, -591626, -1, -10526881, -10461088, -10395295, -10329502, -10263709, -10197916, -10132123, -10066330, -10000537, -9934744, -9868951, -9803158, -9737365, -9671572, -9605779, -9539986, -9474193, -9408400, -9342607, -9276814, -9211021, -9145228, -9079435, -9013642, -8947849, -8882056, -8816263, -8750470, -8684677, -8618884, -8553091, -8487298, -8421505, -8355712, -8289919, -8224126, -8158333, -8092540, -8026747, -7960954, -7895161, -7829368, -7763575, -7697782, -7631989, -7566196, -7500403, -7434610, -7368817, -7303024, -7237231, -7171438, -7105645, -7039852, -6974059, -6908266, -6842473, -6776680, -6710887, -6645094, -6579301, -6513508, -6447715, -6381922, -6316129, -6250336, -6184543, -6118750, -6052957, -5987164, -5921371, -5855578, -5789785, -5723992, -5658199, -5592406, -5526613, -5460820, -5395027, -5329234, -5263441, -5197648, -5131855, -5066062, -5000269, -4934476, -4868683, -4802890, -4737097, -4671304, -4605511, -4539718, -4473925, -4408132, -4342339, -4276546, -4210753, -4144960, -4079167, -4013374, -3947581, -3881788, -3815995, -3750202, -3684409, -3618616, -3552823, -3487030, -3421237, -3355444, -3289651, -3223858, -3158065, -3092272, -3026479, -2960686, -2894893, -2829100, -2763307, -2697514, -2631721, -2565928, -2500135, -2434342, -2368549, -2302756, -2236963, -2171170, -2105377, -2039584, -1973791, -1907998, -1842205, -1776412, -1710619, -1644826, -1579033, -1513240, -1447447, -1381654, -1315861, -1250068, -1184275, -1118482, -1052689, -986896, -921103, -855310, -789517, -723724, -657931, -592138, -526345, -460552, -394759, -328966, -263173, -197380, -131587, -1 };
             pars.SetValue("PALETTE", pal);
        }

        public override void Configure()
        {            
            Generic2DFractalSettings dia = new Generic2DFractalSettings();
            dia.FractalType = "FracMaster.NewtonFractalByIterationsRequired";
            dia.Parameters = (IFractalParameters)this.Parameters.Clone();

            if (dia.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Parameters = dia.Parameters;
            }
        }

        override protected void PartialRender(object P)
        {
            PartialRenderIterationsNeededToReachRoot(P);
        }

        protected void PartialRenderIterationsNeededToReachRoot(object P)
        {

            object[] o = (object[])P;
            int offset = (int)o[0];
            int lines = (int)o[1];
            int[] dst = (int[])o[2];
             
            RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)o[3];
            AutoResetEvent completed = (AutoResetEvent)o[4];

            int width = (int)pars.GetValue("WIDTH");
            int heigth = (int)pars.GetValue("HEIGHT");
            int iterations = (int)pars.GetValue("ITERATIONS") - 1;
            Int32[] Palette = (Int32[])pars.GetValue("PALETTE");

            double a = (double)pars.GetValue("A");
            double W = (double)pars.GetValue("W");
            double H = (double)pars.GetValue("H");
            double X = (double)pars.GetValue("X");
            double Y = (double)pars.GetValue("Y");
           
            int iter = 0;
            int idx = 0;
            double xs = (X - W / 2.0);
            double ys = (Y - H / 2.0);
            double xd = W / (double)width;
            double yd = H / (double)heigth;
            double y1 = ys + yd * offset;

            
            for (int y = offset; y < offset + lines; y++)
            {
                idx = y * width;
                double x1 = xs;

                for (int x = 0; x < width; x++)
                {
                    iter = 0;

                    // newton fractal formula:

                    // zn+1 = zn - a* p(zn)/p'(zn)
                    // were p(z): 
                    //              z^3-1   a: 1,0 ..... 0,5


                    Complex zn = new Complex(x1,y1);
                    Complex pz = new Complex(1,0);
                    Complex pzd = new Complex(1,0);
                    Complex Att1 = new Complex(1.25992  ,  0);
                    Complex Att2 = new Complex(-0.629961, -1.09112);
                    Complex Att3 = new Complex(-0.629961,  1.09112);

                    if (x1 == 0 && y1 == 0)
                    {
                        iter = 0;
                    }
                    else
                    {
                        while ((iter < iterations) && pz.GetModulusSquared() > 0.00000001)
                        {                            
                            pz =  Complex.Pow(zn, 3) - 2;
                            pzd = 3 * Complex.Pow(zn, 2);
                            zn = (zn - a * pz / pzd);
                            iter++;                           
                        }
                    }

                    iter = iter % Palette.Length;
                    dst[idx++] = Palette[iter];
                    x1 += xd;
                }
                y1 += yd;
                lines_rendered++;
                if (lines_rendered % 40 == 0)
                {
                    status_clbk(100.0f * ((float)lines_rendered) / heigth);
                }
            }
            completed.Set();
        }

         
    }
}
