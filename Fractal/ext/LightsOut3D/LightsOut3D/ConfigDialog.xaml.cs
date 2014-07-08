using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace LightsOut3D
{
  /// <summary>
  /// Interaktionslogik für ConfigDialog.xaml
  /// </summary>
  public partial class ConfigDialog : Window
  {
    public ConfigDialog()
    {
      InitializeComponent();
    }

    private void Window_Loaded(object sender, RoutedEventArgs e)
    {
      bool allowPlay = Properties.Settings.Default.AllowInteractive;
      cbAllowInteractive.IsChecked = allowPlay;
      gbDifficulty.IsEnabled = allowPlay;
      int difficulty = Properties.Settings.Default.Difficulty;
      switch(difficulty) {
        case 0:
          rbEasy.IsChecked = true;
          break;
        case 1:
          rbMedium.IsChecked = true;
          break;
        default:
          rbHard.IsChecked = true;
          break;
      }
    }

    private void btnOk_Click(object sender, RoutedEventArgs e)
    {
      Properties.Settings.Default.AllowInteractive = cbAllowInteractive.IsChecked == true;
      if(rbEasy.IsChecked == true)
        Properties.Settings.Default.Difficulty = 0;
      else if(rbMedium.IsChecked == true)
        Properties.Settings.Default.Difficulty = 1;
      else
        Properties.Settings.Default.Difficulty = 2;
      Properties.Settings.Default.Save();
      this.Close();
    }

    private void btnCancel_Click(object sender, RoutedEventArgs e)
    {
      this.Close();
    }

    private void cbAllowInteractive_Checked(object sender, RoutedEventArgs e)
    {
      gbDifficulty.IsEnabled = cbAllowInteractive.IsChecked == true;
    }

  }
}
