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

		IFractalDrawing Drawing { get { return new FormsDrawing (800, 600); } }

        void OnLeaf(object sender, EventArgs e)
        {
			WithWaitCursor(() => Leaf.execute(Drawing));
        }

        void OnFern(object sender, EventArgs e)
        {
			WithWaitCursor(() => Fern.execute(Drawing));
        }

        void OnKidney(object sender, EventArgs e)
        {
			WithWaitCursor(() => Kidney.execute(Drawing));
        }

        void OnColourTree(object sender, EventArgs e)
        {
			WithWaitCursor(() => ColourTree.execute(Drawing));
        }

        void OnRainbowFeather(object sender, EventArgs e)
        {
			WithWaitCursor(() => RainbowFeather.execute(Drawing));
        }

        void OnSpiralThing(object sender, EventArgs e)
        {
			WithWaitCursor(() => SpiralThing.execute(Drawing));
        }

        void OnCircles(object sender, EventArgs e)
        {
			WithWaitCursor(() => Circles.execute(Drawing));
        }

		void OnCircles2(object sender, EventArgs e)
		{
			WithWaitCursor(() => Circles2.execute(Drawing));
		}

        void WithWaitCursor(Action action)
        {
            Cursor.Current = Cursors.WaitCursor;
            action();
            Cursor.Current = Cursors.Arrow;
        }
    }
}
