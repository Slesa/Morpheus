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

        void OnLeafClick(object sender, RoutedEventArgs e)
        {
            var result = Leaf.execute;
        }

        void OnFernClick(object sender, RoutedEventArgs e)
        {
            var result = Fern.execute;
        }

        void OnKidneyClick(object sender, RoutedEventArgs e)
        {
            var result = Kidney.execute;
        }

        void OnColourTreeClick(object sender, RoutedEventArgs e)
        {
            var result = ColourTree.execute;
        }

        void OnRainbowFeatherClick(object sender, RoutedEventArgs e)
        {
            var result = RainbowFeather.execute;
        }

        void OnSpiralThingClick(object sender, RoutedEventArgs e)
        {
            var result = SpiralThing.execute;
        }

        void OnCirclesClick(object sender, RoutedEventArgs e)
        {
            var result = Circles.execute;
        }
    }
}
