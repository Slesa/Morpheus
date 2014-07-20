using System;
using System.Windows.Forms;

namespace FracMaster.Forms
{
    // http://strangelights.com/blog/archive/2006/08/08/1312.aspx
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
