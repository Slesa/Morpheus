using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace IniConfig.Editor.Theme.Controls
{
    public class IconButton : Button
    {
        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(IconButton), new PropertyMetadata(default(ImageSource)));

        public ImageSource Icon
        {
            get { return (ImageSource)GetValue(IconProperty); }
            set { SetValue(IconProperty, value); }
        }
    }
}