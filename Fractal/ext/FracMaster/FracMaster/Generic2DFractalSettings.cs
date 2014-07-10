using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FracMaster
{
    public partial class Generic2DFractalSettings : Form
    {
        IFractalParameters pars = null;
        Bitmap preview = null;
        String fractalType = "FracMaster.MandelbrotFractal";

        public IFractalParameters Parameters
        {
            set
            {
                pars = value;
                ParametersToDialog();
                CalcPreview();
            }
            get
            {
                return pars;
            }
        }

        public String FractalType
        {
            set
            {
                fractalType = value;
            }
        }

        public Generic2DFractalSettings()
        {
            InitializeComponent();
        }

        private void ParametersToDialog()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(ParametersToDialog));
            }
            else
            {
                this.tb_X.Text = ((double)pars.GetValue("X")).ToString();
                this.tb_Y.Text = ((double)pars.GetValue("Y")).ToString();
                this.tb_W.Text = ((double)pars.GetValue("W")).ToString();
                this.tb_H.Text = ((double)pars.GetValue("H")).ToString();
                this.tb_Width.Text = ((int)pars.GetValue("WIDTH")).ToString();
                this.tb_Height.Text = ((int)pars.GetValue("HEIGHT")).ToString();
                this.tb_Iterations.Text = ((int)pars.GetValue("ITERATIONS")).ToString();
                this.checkBox1.Checked = (int)(pars.GetValue("RENDER_INTERPOLATED", 0))==1 ? true:false;
                this.checkBox2.Checked = (int)(pars.GetValue("APPLY_BILINEAR_FILTER", 0)) == 1 ? true : false;                 

            }
        }

        private bool DialogValuesToParamters()
        {           
                try
                {
                    double x = Convert.ToDouble(tb_X.Text);
                    pars.SetValue("X", x);

                    double y = Convert.ToDouble(tb_Y.Text);
                    pars.SetValue("Y", y);

                    double w = Convert.ToDouble(tb_W.Text);
                    pars.SetValue("W", w);

                    double h = Convert.ToDouble(tb_H.Text);
                    pars.SetValue("H", h);

                    int width = Convert.ToInt32(tb_Width.Text);
                    pars.SetValue("WIDTH", width);

                    int height = Convert.ToInt32(tb_Height.Text);
                    pars.SetValue("HEIGHT", height);

                    int iterations = Convert.ToInt32(tb_Iterations.Text);
                    pars.SetValue("ITERATIONS", iterations);

                    int renderInterpolated = checkBox1.Checked == true ? 1 : 0;
                    pars.SetValue("RENDER_INTERPOLATED", renderInterpolated);

                    int applyBilinerFilter = checkBox2.Checked == true ? 1 : 0;
                    pars.SetValue("APPLY_BILINEAR_FILTER", applyBilinerFilter);

                    return true;
                }
                catch { }

                return false;
             
        }

        private void RenderComplete(Bitmap bmp, int ErrorCode)
        {
            if (ErrorCode == 0)
            {
                preview = bmp;               
            }
            UpdatePreview();
            
        }

        private void UpdatePreview()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdatePreview));
            }
            else
            {
                this.pictureBox1.Image = preview;
                button1.Enabled = true;
            }
        }

        private void RenderStatusUpdated(float pcnt)
        {

        }

        private void CalcPreview()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(CalcPreview));
            }
            else
            {
                if (fractalType=="FracMaster.JuliaFractal")
                {
                    JuliaFractal f = new JuliaFractal();
                    f.Parameters = (IFractalParameters)pars.Clone();
                    f.Parameters.SetValue("WIDTH", 128);
                    f.Parameters.SetValue("HEIGHT", 128);
                    f.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                  new RenderResult.RenderStatus(RenderStatusUpdated));
                }
                else if (fractalType == "FracMaster.NewtonFractal" ||
                         fractalType == "FracMaster.NewtonFractalByIterationsRequired" )
                {
                    NewtonFractalByIterationsRequired f = new NewtonFractalByIterationsRequired();
                    f.Parameters = (IFractalParameters)pars.Clone();
                    f.Parameters.SetValue("WIDTH", 128);
                    f.Parameters.SetValue("HEIGHT", 128);
                    f.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                  new RenderResult.RenderStatus(RenderStatusUpdated));
                }
                else
                {
                    MandelbrotFractal f = new MandelbrotFractal();
                    f.Parameters = (IFractalParameters)pars.Clone();
                    f.Parameters.SetValue("WIDTH", 128);
                    f.Parameters.SetValue("HEIGHT", 128);
                    f.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                  new RenderResult.RenderStatus(RenderStatusUpdated));
                }
                button1.Enabled = false;
            }
        }

        private void OnButtonPreviewClick(object sender, EventArgs e)
        {
            if (DialogValuesToParamters() == true)
            {
                CalcPreview();
            }
        }

        private void OnButtonOkClick(object sender, EventArgs e)
        {
            if (DialogValuesToParamters() == true)
            {
                DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void OnButtonCancelClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void OnButtonEditPaletteClick(object sender, EventArgs e)
        {
            Int32[] Palette = (Int32[])pars.GetValue("PALETTE");
            EditPaletteDialog dia = new EditPaletteDialog();
            dia.Palette = (Int32[])Palette.Clone();
            if (dia.ShowDialog() == DialogResult.OK)
            {
                pars.SetValue("PALETTE",dia.Palette);
                CalcPreview();
            }
        }

         
    }
}