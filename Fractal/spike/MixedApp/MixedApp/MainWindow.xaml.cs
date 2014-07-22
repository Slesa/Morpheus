using System;
using System.Windows;
using System.Windows.Input;
using Fractals;
using Cursors = System.Windows.Input.Cursors;

namespace MixedApp
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        IFractalDrawing Drawing { get { return null; } }

        void OnLeafClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => Leaf.execute(Drawing));
        }

        void OnFernClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => Fern.execute(Drawing));
        }

        void OnKidneyClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => Kidney.execute(Drawing));
        }

        void OnColourTreeClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => ColourTree.execute(Drawing));
        }

        void OnRainbowFeatherClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => RainbowFeather.execute(Drawing));
        }

        void OnSpiralThingClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => SpiralThing.execute(Drawing));
        }

        void OnCirclesClick(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => Circles.execute(Drawing));
        }

        void OnCircles2Click(object sender, RoutedEventArgs e)
        {
            //WithWaitCursor(() => Circles2.execute(Drawing));
        }
       
        void WithWaitCursor(Action action)
        {
            Mouse.OverrideCursor = Cursors.Wait;
            action();
            Mouse.OverrideCursor = null;
        }
    }
}
