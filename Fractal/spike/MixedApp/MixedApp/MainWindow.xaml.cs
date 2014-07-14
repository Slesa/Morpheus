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
            Leaf.execute();
        }

        void OnFernClick(object sender, RoutedEventArgs e)
        {
            Fern.execute();
        }

        void OnKidneyClick(object sender, RoutedEventArgs e)
        {
            Kidney.execute();
        }

        void OnColourTreeClick(object sender, RoutedEventArgs e)
        {
            ColourTree.execute();
        }

        void OnRainbowFeatherClick(object sender, RoutedEventArgs e)
        {
             RainbowFeather.execute();
        }

        void OnSpiralThingClick(object sender, RoutedEventArgs e)
        {
            SpiralThing.execute();
        }

        void OnCirclesClick(object sender, RoutedEventArgs e)
        {
            Circles.execute();
        }
    }
}
