using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Reflection;
using System.IO;

using ComplexMath;

namespace FracMaster
{
    public partial class MDIForm : Form
    {
        public MDIForm()
        {
            InitializeComponent();
        }

        private void fractalSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
           
        }
         
        private void testFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal =  new TestFractal();       
            frmchild.Show();
            frmchild.Text = "Test Fractal";
        }

        private void mandelbrotFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal = new MandelbrotFractal();
            frmchild.Show();
            frmchild.Text = "Mandelbrot Fractal";
        }

        private void juliaFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal = new JuliaFractal();
            frmchild.Show();
            frmchild.Text = "Julia Fractal";
        }

        private void newtonFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal = new NewtonFractalByIterationsRequired();
            frmchild.Show();
            frmchild.Text = "Newton Fractal - Iterations Required";
        }

        
        private void loadFractalFromStream(Stream s)
        {
            // ToDo get type of fractal and load it!
            XmlDocument xmldoc = new XmlDocument();
            xmldoc.Load(s);
            XmlNodeList nodes = xmldoc.GetElementsByTagName("frac");
            if (nodes.Count == 1)
            {
                try
                {
                    s.Position = 0;
                    String type = nodes[0].Attributes["type"].Value;

                    if (type == "FracMaster.MandelbrotFractal")
                    {
                        FractalForm frmchild = new FractalForm();
                        frmchild.MdiParent = this;
                        frmchild.Fractal = new MandelbrotFractal();
                        frmchild.Fractal.ReadFromXml(s);
                        frmchild.Show();
                        frmchild.Text = "Mandelbrot Fractal";
                    }
                    else if (type == "FracMaster.JuliaFractal")
                    {
                        FractalForm frmchild = new FractalForm();
                        frmchild.MdiParent = this;
                        frmchild.Fractal = new JuliaFractal();
                        frmchild.Fractal.ReadFromXml(s);
                        frmchild.Show();
                        frmchild.Text = "Julia Fractal";
                    }
                    else if (type == "FracMaster.NewtonFractal" ||
                             type == "FracMaster.NewtonFractalByIterationsRequired")
                    {
                        FractalForm frmchild = new FractalForm();
                        frmchild.MdiParent = this;
                        frmchild.Fractal = new NewtonFractalByIterationsRequired();
                        frmchild.Fractal.ReadFromXml(s);
                        frmchild.Show();
                        frmchild.Text = "Newton Fractal - Iterations required";
                    }
                  
                    else
                    {
                        // ignore
                    }
                }
                catch { }
            }
        }

        private void loadFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // load fractal here
            OpenFileDialog dia = new OpenFileDialog();
            dia.Filter = "xml file (*.xml)|*.xml";

            if (dia.ShowDialog() == DialogResult.OK)
            {
                Stream s = new FileStream(dia.FileName,FileMode.Open);
                loadFractalFromStream(s);
                 
            }
        }

        private void aboutFracMasterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("FracMaster \n\r\n\r(C) 2009 Zimmermann Stephan");
        }

        

        private void cascadedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        private void tileHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void tileVerticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }

        private void newtonFractal01ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_newton_01.xml");
            loadFractalFromStream(s);
        }

        private void mandelbrot01ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_mandel_01.xml");
            loadFractalFromStream(s);
        }

        private void mandelbrot02ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_mandel_02.xml");
            loadFractalFromStream(s);
        }

        private void mandelbrot03ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_mandel_03.xml");
            loadFractalFromStream(s);
        }

        private void julia01ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_julia_01.xml");
            loadFractalFromStream(s);
        }

        private void mandelbrot04ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_mandel_04.xml");
            loadFractalFromStream(s);
        }

        private void mandelbrot05ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stream s = Assembly.GetExecutingAssembly().GetManifestResourceStream("FracMaster.BuildInFractals.frac_mandel_05.xml");
            loadFractalFromStream(s);
        }

       
    }
}