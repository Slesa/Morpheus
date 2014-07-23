using System.Windows.Forms;
using Fractals;

namespace MixedApp.Forms
{
    public partial class SettingsView : Form
    {
        public SettingsView(IFractal fractal)
        {
            InitializeComponent();

			this.properties.ActiveControl = fractal.Parameters;
        }
    }
}
