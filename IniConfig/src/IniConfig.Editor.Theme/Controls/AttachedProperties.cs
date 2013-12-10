using System.Windows;

namespace IniConfig.Editor.Theme.Controls
{
    public class AttachedProperties
    {
        public static readonly DependencyProperty IconProperty =
            DependencyProperty.RegisterAttached("Icon", typeof (object), typeof (AttachedProperties), new PropertyMetadata(default(object)));

        public static void SetIcon(UIElement element, object value)
        {
            element.SetValue(IconProperty, value);
        }

        public static object GetIcon(UIElement element)
        {
            return (object) element.GetValue(IconProperty);
        }


        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.RegisterAttached("Title", typeof (string), typeof (AttachedProperties), new PropertyMetadata(default(string)));

        public static void SetTitle(UIElement element, string value)
        {
            element.SetValue(TitleProperty, value);
        }

        public static string GetTitle(UIElement element)
        {
            return (string) element.GetValue(TitleProperty);
        }


        public static readonly DependencyProperty SubtitleProperty =
            DependencyProperty.RegisterAttached("Subtitle", typeof (string), typeof (AttachedProperties), new PropertyMetadata(default(string)));

        public static void SetSubtitle(UIElement element, string value)
        {
            element.SetValue(SubtitleProperty, value);
        }

        public static string GetSubtitle(UIElement element)
        {
            return (string) element.GetValue(SubtitleProperty);
        }
    }
}