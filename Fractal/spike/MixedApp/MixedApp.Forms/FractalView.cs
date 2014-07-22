using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Fractals;

namespace MixedApp.Forms
{
    public partial class FractalView : Form
    {
        readonly IFractal _fractal;
        readonly BackgroundWorker _backgroundWorker = new BackgroundWorker();

        public FractalView(IFractal fractal)
        {
            _fractal = fractal;

            InitializeComponent();

            Text = _fractal.Title;
            Width = 800;
            Height = 600;

            this.Resize += OnResize;
        }

        void OnResize(object sender, EventArgs e)
        {
            UpdateFractal();
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            UpdateFractal();
        }

        void UpdateFractal()
        {
            WithWaitCursor(() =>
                {
                    pictureBox.Image = new Bitmap(pictureBox.Width, pictureBox.Height);
                    _fractal.Calculate(new FormsDrawing(pictureBox.Image));
                });
        }

        public FractalView(string title, int width, int height, Image image)
        {
            InitializeComponent();

            Text = title;
            Width = width;
            Height = height;
            pictureBox.Image = image;
        }

        void OnSettings(object sender, System.EventArgs e)
        {

        }

        void OnSave(object sender, System.EventArgs e)
        {

        }

        void OnImage(object sender, System.EventArgs e)
        {

        }

        void WithWaitCursor(Action action)
        {
            Cursor.Current = Cursors.WaitCursor;
            action();
            Cursor.Current = Cursors.Arrow;
        }
    }
}
