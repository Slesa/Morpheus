using System;
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

        void OnLeaf(object sender, EventArgs e)
        {
            var result = Leaf.execute;
        }

        void OnFern(object sender, EventArgs e)
        {
            var result = Fern.execute;
        }

        void OnKidney(object sender, EventArgs e)
        {
            var result = Kidney.execute;
        }

        void OnColourTree(object sender, EventArgs e)
        {
            var result = ColourTree.execute;
        }

        void OnRainbowFeather(object sender, EventArgs e)
        {
            var result = RainbowFeather.execute;
        }

        void OnSpiralThing(object sender, EventArgs e)
        {
            var result = SpiralThing.execute;
        }

        void OnCircles(object sender, EventArgs e)
        {
            var result = Circles.execute;
        }
    }
}
