using System.Drawing;

namespace FracMaster
{
    public static class Utils
    {
        static public int InterpolateColors(int s1, int s2, int weigth)
        {
            var c1 = Color.FromArgb(s1);
            var c2 = Color.FromArgb(s2);

            var red = (byte)(((int)c1.R + ((int)((c2.R - c1.R) * weigth) >> 8)) & 0xff);
            var green = (byte)(((int)c1.G + ((int)((c2.G - c1.G) * weigth) >> 8)) & 0xff);
            var blue = (byte)(((int)c1.B + ((int)((c2.B - c1.B) * weigth) >> 8)) & 0xff);

            return Color.FromArgb(red, green, blue).ToArgb();            
        }
    }
}
