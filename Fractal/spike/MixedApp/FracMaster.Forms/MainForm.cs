using System.Windows.Forms;

namespace FracMaster.Forms
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        void OnMandelbrot(object sender, System.EventArgs e)
        {
            var child = new FractalForm
                {
                    Text = "Mandelbrot Fractal", 
                    Fractal = new MandelbrotFractal(),
                };
            child.Show();
        }

        void OnJulia(object sender, System.EventArgs e)
        {
            var child = new FractalForm
                {
                    Text = "Julia Fractal", 
                    Fractal = new JuliaFractal(),
                };
            child.Show();
        }

        void OnNewton(object sender, System.EventArgs e)
        {
            var child = new FractalForm
                {
                    Text = "Newton Fractal", 
                    Fractal = new NewtonFractalByIterationsRequired(),
                };
            child.Show();
        }

        void OnTest(object sender, System.EventArgs e)
        {
            var child = new FractalForm
                {
                    Text = "Test Fractal", 
                    Fractal = new TestFractal(),
                };
            child.Show();
        }
    }
}
