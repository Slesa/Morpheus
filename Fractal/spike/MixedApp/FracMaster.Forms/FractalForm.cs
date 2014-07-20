using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace FracMaster.Forms
{
    public partial class FractalForm : Form
    {
        IAsyncResult _renderResult;
        string caption = String.Empty;
        bool isRendering = false;
        int LastErrorCode = 0;
        DateTime renderStart = DateTime.MinValue;
        TimeSpan renderTime = new TimeSpan();

        Bitmap LastFractalImage = null;
        float CalculationProgress = 0;

        public FractalForm()
        {
            Fractal = null;
            InitializeComponent();
        }

        public IFractal Fractal { get; set; }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            RenderFractal();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            if (isRendering && _renderResult != null)
            {
                Fractal.EndRender(_renderResult);
            }
            base.OnClosing(e);
        }

        void OnStartRender(object sender, System.EventArgs e)
        {
            RenderFractal();            
        }

        void OnStopRender(object sender, System.EventArgs e)
        {
            InterruptRender();
        }

        void RenderFractal()
        {
            if (_renderResult != null) return;

            caption = Text;
            isRendering = true;

            renderStart = DateTime.Now;
            _renderResult = Fractal.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                            new RenderResult.RenderStatus(RenderStatusUpdated));

            buttonRender.Enabled = false;
            buttonSettings.Enabled = false;
            buttonStop.Enabled = true;
        }

        void InterruptRender()
        {
            if (_renderResult != null)
            {
                Fractal.EndRender(_renderResult);
            }

            buttonRender.Enabled = true;
            buttonStop.Enabled = false;
        }

        void RenderComplete(Bitmap bmp, int errorCode)
        {
            try
            {
                if (_renderResult == null) return;
                renderTime = DateTime.Now - renderStart;
                LastErrorCode = errorCode;

                Fractal.EndRender(_renderResult);
                LastFractalImage = bmp;

                UpdateFormContent();

                _renderResult = null;
                isRendering = false;
            }
            catch { }
        }

        void RenderStatusUpdated(float pcnt)
        {
            try
            {
                CalculationProgress = pcnt;
                UpdateFormCaption();
            }
            catch { }
        }

        void UpdateFormCaption()
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(UpdateFormCaption));
                return;
            }
            var pcnt = (int)CalculationProgress;
            Text = caption + "[" + pcnt + "%]";
        }

        void UpdateFormContent()
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(UpdateFormContent));
                return;
            }
            try
            {
                    Text = caption;
                    //label1.Text = "" + LastFractalImage.Width + "x" + LastFractalImage.Height + " [pix]  rendered in  " + renderTime.TotalMilliseconds + " ms using " + Environment.ProcessorCount + " cpus";

                    buttonStop.Enabled = false;
                    buttonRender.Enabled = true;
                    buttonSettings.Enabled = true;
                    if (LastErrorCode == 0)
                    {
                        pictureBox2.Image = LastFractalImage;
                        pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
                        UpdatePictureBox();
                    }
            }
            catch
            { }
        }

        void UpdatePictureBox()
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(UpdatePictureBox));
                return;
            }
            if (LastFractalImage != null)
            {
                pictureBox2.Width = LastFractalImage.Width + 20;
                pictureBox2.Height = LastFractalImage.Height + 20;

/*
                Point loc = pictureBox2.Location;
                if (pictureBox2.Width < splitContainer2.Panel1.Width)
                {
                    loc.X = (splitContainer2.Panel1.Width - pictureBox2.Width) / 2;
                }
                else
                {
                    loc.X = -splitContainer2.Panel1.HorizontalScroll.Value;
                }

                if (pictureBox2.Height < splitContainer2.Panel1.Height)
                {
                    loc.Y = (splitContainer2.Panel1.Height - pictureBox2.Height) / 2;
                }
                else
                {
                    loc.Y = -splitContainer2.Panel1.VerticalScroll.Value;
                }
                pictureBox2.Location = loc;
*/
            }
        }

        void OnSave(object sender, EventArgs e)
        {
            SaveFileDialog dia = new SaveFileDialog();
            dia.Filter = "xml file (*.xml)|*.xml";

            if ( dia.ShowDialog() == DialogResult.OK )
            {
                Fractal.WriteToXml(dia.FileName);
            }           

        }
    }
}
