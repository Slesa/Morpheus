using System;
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

        public FractalForm()
        {
            Fractal = null;
            InitializeComponent();
        }

        public IFractal Fractal { get; set; }

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
                    label1.Text = "" + LastFractalImage.Width + "x" + LastFractalImage.Height + " [pix]  rendered in  " + renderTime.TotalMilliseconds + " ms using " + Environment.ProcessorCount + " cpus";

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
    }
}
