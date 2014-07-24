using System.Windows.Forms;
using Fractals;

namespace MixedApp.Forms
{
    public partial class SettingsView : Form
    {
        public SettingsView(IFractal fractal)
        {
            InitializeComponent();

			Text = "Settings of " + fractal.Title;
            properties.SelectedObject = fractal.Parameters;
        }

        private void OnApply(object sender, System.EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

    }
}
