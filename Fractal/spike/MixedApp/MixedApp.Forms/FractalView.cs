using System.Drawing;
using System.Windows.Forms;

namespace MixedApp.Forms
{
    public partial class FractalView : Form
    {
        public FractalView(string title, int width, int height, Image image)
        {
            InitializeComponent();

            Text = title;
            Width = width;
            Height = height;
            pictureBox.Image = image;
        }

        private void OnSettings(object sender, System.EventArgs e)
        {

        }

        private void OnSave(object sender, System.EventArgs e)
        {

        }

        private void OnImage(object sender, System.EventArgs e)
        {

        }
    }
}
