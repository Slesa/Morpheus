using System.Windows;
using Fractals;

namespace MixedApp
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            
        }

        void OnFernClick(object sender, RoutedEventArgs e)
        {
            var result = Fern.execute;
        }

        void OnKidneyClick(object sender, RoutedEventArgs e)
        {
            var result = Kidney.execute;
        }

        void OnRainbowFeatherClick(object sender, RoutedEventArgs e)
        {
            var result = RainbowFeather.execute;
        }
    }
}
