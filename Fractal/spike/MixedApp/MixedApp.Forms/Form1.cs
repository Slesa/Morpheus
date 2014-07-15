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
            WithWaitCursor(Leaf.execute);
        }

        void OnFern(object sender, EventArgs e)
        {
            WithWaitCursor(Fern.execute);
        }

        void OnKidney(object sender, EventArgs e)
        {
            WithWaitCursor(Kidney.execute);
        }

        void OnColourTree(object sender, EventArgs e)
        {
            WithWaitCursor(ColourTree.execute);
        }

        void OnRainbowFeather(object sender, EventArgs e)
        {
            WithWaitCursor(RainbowFeather.execute);
        }

        void OnSpiralThing(object sender, EventArgs e)
        {
            WithWaitCursor(SpiralThing.execute);
        }

        void OnCircles(object sender, EventArgs e)
        {
            WithWaitCursor(Circles.execute);
        }

		void OnCircles2(object sender, EventArgs e)
		{
			WithWaitCursor(Circles2.execute);
		}

        void WithWaitCursor(Action action)
        {
            Cursor.Current = Cursors.WaitCursor;
            action();
            Cursor.Current = Cursors.Arrow;
        }
    }
}
