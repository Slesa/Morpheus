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
            new FractalView(new Circles(CirclesParameters.Default)).Show();
        }

        void OnCircles2(object sender, EventArgs e)
        {
            new FractalView(new Circles2(Circles2Parameters.Default)).Show();
        }

        void OnColourTree(object sender, EventArgs e)
        {
            new FractalView(new ColourTree(ColourTreeParameters.Default)).Show();
        }

        void OnFern(object sender, EventArgs e)
        {
            new FractalView(new Fern(FernParameters.Default)).Show();
        }

        void OnKidney(object sender, EventArgs e)
        {
            new FractalView(new Kidney(KidneyParameters.Default)).Show();
        }

        void OnLeaf(object sender, EventArgs e)
        {
            new FractalView(new Leaf(LeafParameters.Default)).Show();
        }

        void OnRainbowFeather(object sender, EventArgs e)
        {
            new FractalView(new RainbowFeather(RainbowFeatherParameters.Default)).Show();
        }

        void OnSpiralThing(object sender, EventArgs e)
        {
            new FractalView(new SpiralThing(SpiralThingParameters.Default)).Show();
        }
    }
}
