using System.Windows;
using System.Windows.Input;
using Microsoft.Practices.Prism.Commands;

namespace IniConfig.Editor.lib.ViewModels
{
    public class MenuBarViewModel
    {
        public MenuBarViewModel()
        {
            LoadCommand = new DelegateCommand(OnLoad);
            SaveCommand = new DelegateCommand(OnSave);
            SaveAsCommand = new DelegateCommand(OnSaveAs);
            QuitCommand = new DelegateCommand(OnQuit);
        }

        public ICommand LoadCommand { get; private set; }

        void OnLoad()
        {

        }

        public ICommand SaveCommand { get; private set; }

        void OnSave()
        {

        }
        
        public ICommand SaveAsCommand { get; private set; }

        void OnSaveAs()
        {

        }

        public ICommand QuitCommand { get; private set; }

        void OnQuit()
        {
            Application.Current.Shutdown();
        }
    }
}