using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace LightsOut3D
{
  /// <summary>
  /// Interaktionslogik für "App.xaml"
  /// </summary>
  public partial class App : Application
  {
    private void Application_Startup(object sender, StartupEventArgs e)
    {
      TheApp = this;
      if(!ParseArgs(e.Args))
        this.Shutdown(-1);
      if(Mode == RunMode.Config) {
        MainWindow = new ConfigDialog();
        if(ParentHandle != IntPtr.Zero) {
          WindowInteropHelper wih = new WindowInteropHelper(MainWindow);
          wih.Owner = ParentHandle;
        }
        MainWindow.ShowDialog();
      }
      else {
        MainWindow = new MainWindow();
        MainWindow.Show();
      }
    }

    private bool ParseArgs(string[] args)
    {
      Mode = RunMode.Config;
      if(args.Length > 0) {
        string arg = args[0].ToLower();
        if(arg.StartsWith("/s")) {
          Mode = RunMode.FullScreen;
        }
        else if(arg.StartsWith("/p")) {
          Mode = RunMode.Preview;
        }
        else if(arg.StartsWith("/c")) {
          Mode = RunMode.Config;
        }
        else {
          MessageBox.Show("Unbekannte Kommandozeilenoption: " + arg, "LightsOut3D", MessageBoxButton.OK, MessageBoxImage.Error);
          return false;
        }
        if(arg.Length > 3) {
          arg = arg.Substring(3);
        }
        else if(args.Length > 1) {
          arg = args[1];
        }
        Int64 handle;
        if(Int64.TryParse(arg, out handle)) {
          ParentHandle = new IntPtr(handle);
        }
        if(Mode == RunMode.Preview && ParentHandle == IntPtr.Zero) {
          MessageBox.Show("Illegale Kommandozeilenoptionen: /p ohne Container-Handle", "LightsOut3D", MessageBoxButton.OK, MessageBoxImage.Error);
          return false;
        }
      }
      return true;
    }

    public enum RunMode
    {
      FullScreen,
      Preview,
      Config
    }

    public RunMode Mode
    {
      get;
      private set;
    }

    public IntPtr ParentHandle
    {
      get;
      private set;
    }

    public static App TheApp
    {
      get;
      private set;
    }
  }
}
