using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FracMaster
{
    public partial class EditPaletteDialog : Form
    {
        Int32[] palette = null;
        int palettewidth = 256;
        int gradientIndexStart = -1;
        int gradientIndexEnd = -1;

        public EditPaletteDialog()
        {
            InitializeComponent();
        }

        public Int32[] Palette
        {
            get
            {
                return palette;
            }
            set
            {
                palette = value;
                ApplyPaletteToForm();
            }
        }

        private void ApplyPaletteToForm()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(ApplyPaletteToForm));
            }
            else
            {
                if (palette != null)
                {
                   
                    int NumColsX = (int)(Math.Sqrt(palette.Length) + 0.5);
                    palettewidth = (NumColsX-1) * 17;

                    SuspendLayout();

                  
                    this.panel1.Controls.Clear();
                    this.panel1.Width = palettewidth;
                    this.panel1.Height = palettewidth;

                    int x = 0;
                    int y = 0;
                    int idx = 0;
                    for (int i = 0; i < palette.Length; i++)
                    {
                        Button b = new Button();
                        b.Width = 16;
                        b.Height = 16;
                        b.Location = new Point(x+1, y+1);
                        b.BackColor = Color.FromArgb(palette[i]);                       
                        b.FlatStyle = FlatStyle.Flat;
                        b.FlatAppearance.BorderSize = 0;
                        b.TabIndex = i;
                        x += 17;
                        if (idx++ >= NumColsX-1)
                        {
                            x = 0;
                            y += 17;
                            idx = 0;
                        }
                        this.panel1.Controls.Add(b);
                        
                        b.Click += new EventHandler(b_Click);
                        b.ContextMenuStrip = contextMenuStrip1;
                    }

                    ResumeLayout();
                    UpdatePaletteBox();
                }
            }
        }

        void b_Click(object sender, EventArgs e)
        {
            ColorDialog d = new ColorDialog();
            Button btn = (Button)sender;
            if (d.ShowDialog() == DialogResult.OK)
            {
                
                btn.BackColor = d.Color;
                palette[btn.TabIndex] = d.Color.ToArgb();
                
            }
           
        }

        

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }

        void UpdatePaletteBox()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdatePaletteBox));
            }
            else
            {
                 
                panel1.Width = palettewidth + 20;
                panel1.Height = palettewidth + 20;

                Point loc = panel1.Location;

                if (panel1.Width < splitContainer1.Panel1.Width)
                {
                    loc.X = (splitContainer1.Panel1.Width - panel1.Width) / 2;
                }
                else
                {
                    loc.X = -splitContainer1.Panel1.HorizontalScroll.Value;
                }

                if (panel1.Height < splitContainer1.Panel1.Height)
                {
                    loc.Y = (splitContainer1.Panel1.Height - panel1.Height) / 2;
                }
                else
                {
                    loc.Y = -splitContainer1.Panel1.VerticalScroll.Value;
                }

                panel1.Location = loc;
             
            }
        }

        private void splitContainer1_Panel1_SizeChanged(object sender, EventArgs e)
        {
            UpdatePaletteBox();
        }

        private void setAsStartIndexForGradientToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // ToDO: find out which button is selected
            try
            {
                ToolStripDropDownItem it = (ToolStripDropDownItem)sender;
                ContextMenuStrip cx = (ContextMenuStrip)it.Owner;
                Button btn = (Button)cx.SourceControl;
                gradientIndexStart = btn.TabIndex;                              
                calculateGradientToolStripMenuItem.Enabled = true;
            }
            catch
            {

            }
        }

        private void calculateGradientToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // ToDO: find out which button is selected
            try
            {
                ToolStripDropDownItem it = (ToolStripDropDownItem)sender;
                ContextMenuStrip cx = (ContextMenuStrip)it.Owner;
                Button btn = (Button)cx.SourceControl;
                gradientIndexEnd = btn.TabIndex;

                if (gradientIndexEnd >= 0 && gradientIndexEnd >= 0)
                {
                    if( gradientIndexEnd < gradientIndexStart )
                    {
                        int temp = gradientIndexStart;
                        gradientIndexStart = gradientIndexEnd;
                        gradientIndexEnd = temp;
                    }

                    Color col1 = Color.FromArgb(palette[gradientIndexStart]);
                    Color col2 = Color.FromArgb(palette[gradientIndexEnd]);
                    int Amount = gradientIndexEnd - gradientIndexStart ;
                    
                    double rs = col1.R;
                    double gs = col1.G;
                    double bs = col1.B;
                    double re = col2.R;
                    double ge = col2.G;
                    double be = col2.B;
                    Hashtable ColorsByIndex = new Hashtable();

                    for (int i = 0; i < Amount; i++)
                    {
                        double pctn = 1.0 * i / Amount;
                        double rc = rs * (1 - pctn) + re * pctn;
                        double gc = gs * (1 - pctn) + ge * pctn;
                        double bc = bs * (1 - pctn) + be * pctn;

                        Color ColC = Color.FromArgb((int)rc, (int)gc, (int)bc);
                        ColorsByIndex[i + gradientIndexStart] = ColC;
                        palette[i + gradientIndexStart] = ColC.ToArgb();
                    }

                    foreach (Button b in panel1.Controls)
                    {
                        int idx = b.TabIndex;
                        if (ColorsByIndex.ContainsKey(idx))
                        {
                            b.BackColor = (Color)ColorsByIndex[idx];
                        }
                    }

                    gradientIndexStart = -1;
                    gradientIndexEnd = -1;
                }

                calculateGradientToolStripMenuItem.Enabled = false;
            }
            catch
            {

            }
        }

        private void resetStartIndexForGradientToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}