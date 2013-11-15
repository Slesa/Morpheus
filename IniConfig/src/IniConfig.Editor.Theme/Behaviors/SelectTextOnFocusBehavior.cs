using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace IniConfig.Editor.Theme.Behaviors
{
    public class SelectTextOnFocusBehavior : Behavior<TextBox>
    {
        protected override void OnAttached()
        {
            base.OnAttached();

            // This way, the first click into the textbox will keep the text unselected. A second click will select the text.
            //AssociatedObject.GotKeyboardFocus += OnKeyboardFocusSelectText;
            //AssociatedObject.GotMouseCapture += OnMouseCapture;

            // This way, the One-Click-Select does not work if the text has already the keyboard focus. Seems to be the better solution.
            AssociatedObject.GotFocus += OnKeyboardFocusSelectText;
            AssociatedObject.PreviewMouseDown += IgnoreMouseButton;
        }

        protected override void OnDetaching()
        {
            base.OnDetaching();

            //AssociatedObject.GotKeyboardFocus -= OnKeyboardFocusSelectText;
            //AssociatedObject.PreviewMouseDown -= IgnoreMouseButton;

            AssociatedObject.GotFocus -= OnKeyboardFocusSelectText;
            AssociatedObject.PreviewMouseDown -= IgnoreMouseButton;

        }

        void OnKeyboardFocusSelectText(object sender, RoutedEventArgs e)
        {
            AssociatedObject.SelectAll();
        }

        void OnMouseCapture(object sender, MouseEventArgs e)
        {
            AssociatedObject.SelectAll();
        }

        void IgnoreMouseButton(object sender, MouseButtonEventArgs e)
        {
            var textBox = sender as TextBox;
            if (textBox == null || textBox.IsKeyboardFocusWithin) return;
            e.Handled = true;
            textBox.Focus();
        }
    }
}