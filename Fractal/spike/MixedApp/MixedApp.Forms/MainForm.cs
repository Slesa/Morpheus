using System;
using System.Drawing;
using System.Windows.Forms;
using Fractals;

namespace MixedApp.Forms
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        void OnCircles(object sender, EventArgs e)
        {
			new FractalView(new Circles(new CirclesParameters(CirclesParameters.DefaultRadius))).Show();
        }

        void OnCircles2(object sender, EventArgs e)
        {
			new FractalView(new Circles2(new Circles2Parameters(Circles2Parameters.DefaultRadius))).Show();
        }

        void OnColourTree(object sender, EventArgs e)
        {
//            new FractalView(new ColourTree()).Show();
        }

        void OnFern(object sender, EventArgs e)
        {
//            new FractalView(new Fern()).Show();
        }

        void OnKidney(object sender, EventArgs e)
        {
//            new FractalView(new Kidney()).Show();
        }

        void OnLeaf(object sender, EventArgs e)
        {
//            new FractalView(new Leaf()).Show();
        }

        void OnRainbowFeather(object sender, EventArgs e)
        {
//            new FractalView(new RainbowFeather()).Show();
        }

        void OnSpiralThing(object sender, EventArgs e)
        {
//            new FractalView(new SpiralThing()).Show();
        }
    }
}
