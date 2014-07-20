using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace FracMaster
{
    /*
    public class FractalForm : Form
    {
        #region MEMBERS

        Point dragStart = Point.Empty;
        Point dragEnd = Point.Empty;
        Rectangle r = new Rectangle();
        bool isDragging = false;
        bool isZooming = false;

        #endregion

        public FractalForm()
        {            
            InitializeComponent();
            pictureBox2.MouseMove += new MouseEventHandler(pictureBox2_MouseMove);
            pictureBox2.MouseDown += new MouseEventHandler(pictureBox2_MouseDown);
            pictureBox2.MouseUp += new MouseEventHandler(pictureBox2_MouseUp);
            splitContainer2.Panel1.SizeChanged += new System.EventHandler(this.splitContainer2_Panel1_SizeChanged);           
        }

        private void splitContainer2_Panel1_SizeChanged(object sender, EventArgs e)
        {
            UpdatePictureBox();
        }

        

        void OnImageOriginDragged(int dx, int dy)
        {
            ((Generic2DFractal)frac).SetOrigin(dx, dy);          

            RenderFractal();
        }

        void OnControlPointDragged(int dx, int dy)
        {
            ((Generic2DFractal)frac).SetControlParameter(dx, dy);

            RenderFractal();

        }
        bool ScreenToFractal(double X, double Y, out double XF, out double YF)
        {
            if (pictureBox2.Image != null)
            {
                int off_x = pictureBox2.Width - pictureBox2.Image.Width;
                int off_y = pictureBox2.Height - pictureBox2.Image.Height;

                off_x /= 2;
                off_y /= 2;

                if (X > off_x && X < (off_x + pictureBox2.Image.Width) &&
                    Y > off_y && Y < (off_y + pictureBox2.Image.Height))
                {
                    X -= off_x;
                    Y -= off_y;
                    IFractalParameters pars = frac.Parameters;

                    double FracX = (double)pars.GetValue("X");
                    double FracY = (double)pars.GetValue("Y");
                    double FracWidth = (double)pars.GetValue("W");
                    double FracHeight = (double)pars.GetValue("H");
                    double FracX1 = FracX - 0.5 * FracWidth;
                    double FracY1 = FracY - 0.5 * FracHeight;
                   
                    // PicW : X = FracWidth : dxf
                    // pictureBox2.Image.Width : X = FracWidth : dxf
                    double dxf = FracWidth * X / pictureBox2.Image.Width;
                    double dyf = FracHeight * Y / pictureBox2.Image.Height;
                    XF = FracX1 + dxf;
                    YF = FracY1 + dyf;
                    return true;
                }
            }
            XF = 0;
            YF = 0;
            return false;
        }

        void OnImageZoomed(Point p1, Point p2)
        {
            IFractalParameters pars = frac.Parameters;
            
            double x1f,y1f;
            double x2f, y2f;

            ScreenToFractal(p1.X, p1.Y, out x1f, out y1f);
            ScreenToFractal(p2.X, p2.Y, out x2f, out y2f);

            double XN = (x2f + x1f) / 2.0;
            double YN = (y2f + y1f) / 2.0;
            double WFN = (x2f - x1f);
            double HFN = (y2f - y1f);
            pars.SetValue("X", XN);
            pars.SetValue("Y", YN);
            pars.SetValue("W", WFN);
            pars.SetValue("H", HFN);
            RenderFractal();
        }

        void pictureBox2_MouseUp(object sender, MouseEventArgs e)
        {
            if (IsMouseOverImage(e.X, e.Y) && 
                dragStart != Point.Empty && 
                e.Button == MouseButtons.Right)
            {
                // begin drag
                dragEnd = new Point(e.X, e.Y);
                OnImageOriginDragged(dragEnd.X - dragStart.X, dragEnd.Y - dragStart.Y);
            }
            else if (IsMouseOverImage(e.X, e.Y) &&
                     dragStart != Point.Empty &&
                     e.Button == MouseButtons.Middle)
            {
                // begin drag
                dragEnd = new Point(e.X, e.Y);
                OnControlPointDragged(dragEnd.X - dragStart.X, dragEnd.Y - dragStart.Y);
            }
            else if (IsMouseOverImage(e.X, e.Y) && dragStart != Point.Empty && e.Button == MouseButtons.Left)
            {
                double ar = 1.0;

                if (pictureBox2.Image != null)
                {
                    ar = (double)pictureBox2.Image.Width / (double)pictureBox2.Image.Height;
                }

                double drw = e.X - dragStart.X;
                double drh = e.Y - dragStart.Y;

                if (drw > drh)  drh = drw / ar;                 
                else            drw = drh * ar;

                dragEnd = new Point((int)(dragStart.X + drw), (int)(dragStart.Y + drh));                 
                OnImageZoomed( dragStart , dragEnd );
            }

            isZooming = false;
            isDragging = false;
            dragStart = Point.Empty;
            dragEnd = Point.Empty;         
            this.Cursor = Cursors.Default;
        }

        void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            if (IsMouseOverImage(e.X, e.Y) && 
                dragStart == Point.Empty && 
                e.Button == MouseButtons.Right &&
                !isRendering)
            {
                // begin drag
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.SizeAll;
                isDragging = true;
            }
            else if (IsMouseOverImage(e.X, e.Y) &&
            dragStart == Point.Empty &&
            e.Button == MouseButtons.Middle &&
            !isRendering)
            {
                // begin drag
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.Cross;
                isDragging = true;
            }
            else if (IsMouseOverImage(e.X, e.Y) && 
                     dragStart == Point.Empty && 
                     e.Button == MouseButtons.Left &&
                     !isRendering)
            {
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.IBeam;
                isZooming = true;
                // begin zoom
                Point startPoint = pictureBox2.PointToScreen(new Point(e.X, e.Y));
                r = new Rectangle(startPoint.X, startPoint.Y, 0, 0);              
            }
            else
            {
                dragStart = Point.Empty;
                dragEnd = Point.Empty;
                Cursor = Cursors.Default;
            }
        }

        void pictureBox2_MouseMove(object sender, MouseEventArgs e)
        {
            
            if (!isDragging && !isZooming && !isRendering)
            {
                if (IsMouseOverImage(e.X, e.Y))
                {                     
                    this.Cursor = Cursors.Hand;                     
                }
                else
                {
                    this.Cursor = Cursors.Default;
                }
            }           
            else if (isZooming && !isRendering)
            {                 
                ControlPaint.DrawReversibleFrame(r, this.BackColor, FrameStyle.Dashed);

                Point endPoint = pictureBox2.PointToScreen(new Point(e.X, e.Y));
                Point startPoint = pictureBox2.PointToScreen(dragStart);
                double ar = 1.0;

                if (pictureBox2.Image != null)
                {
                    ar = (double)pictureBox2.Image.Width / (double)pictureBox2.Image.Height;
                }

                double drw = endPoint.X - startPoint.X;
                double drh = endPoint.Y - startPoint.Y;

                if (drw > drh)      drh = drw / ar;
                else                drw = drh * ar;

                r = new Rectangle(startPoint.X, startPoint.Y, (int)drw, (int)drh);               
                
                ControlPaint.DrawReversibleFrame(r, this.BackColor, FrameStyle.Dashed);               
            }
        }

        bool IsMouseOverImage(int X, int Y)
        {
            if (pictureBox2.Image != null)
            {
                int off_x = pictureBox2.Width - pictureBox2.Image.Width;
                int off_y = pictureBox2.Height - pictureBox2.Image.Height;

                off_x /= 2;
                off_y /= 2;

                if (X > off_x && X < (off_x + pictureBox2.Image.Width) &&
                     Y > off_y && Y < (off_y + pictureBox2.Image.Height))
                {
                    return true;
                }
            }
            return false;
        }

        private void OnChangefractalSettings(object sender, EventArgs e)
        {
            try
            {
                frac.Configure();
                 
            }
            catch { }
        }
       


        private void OnsaveImageAsToolStripMenuItemClicked(object sender, EventArgs e)
        {
            if (LastFractalImage != null)
            {
                SaveFileDialog dia = new SaveFileDialog();
                dia.Filter = "png file (*.png)|*.png";

                if (dia.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        this.LastFractalImage.Save(dia.FileName);
                    }
                    catch  { }
                }
            }
        }
 

    }
     * */
}