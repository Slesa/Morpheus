using System.Windows;
using IniConfig.Editor.lib;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Helpers;
using IniConfig.Editor.lib.Resources;
using IniConfig.Editor.lib.ViewModels;
using IniConfig.Editor.lib.Views;
using Microsoft.Practices.Prism.Events;
using Microsoft.Practices.Prism.Regions;
using Microsoft.Practices.Prism.UnityExtensions;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;

namespace IniConfig.Editor
{
    public class Bootstrapper : UnityBootstrapper
    {
        protected override DependencyObject CreateShell()
        {
            return ServiceLocator.Current.GetInstance<Shell>();
        }

        protected override void InitializeShell()
        {
            base.InitializeShell();

            Application.Current.MainWindow = (Window) Shell;
            Application.Current.MainWindow.Show();

            var eventAggregator = Container.Resolve<IEventAggregator>();
            eventAggregator.GetEvent<ShowStatusMessageEvent>().Publish(Strings.Msg_Ready);

        }

        protected override void ConfigureContainer()
        {
            base.ConfigureContainer();

            RegisterTypeIfMissing(typeof (IRegionManager), typeof (RegionManager), true);
            RegisterTypeIfMissing(typeof (IProvideSettings), typeof (SettingsProvider), true);
            RegisterTypeIfMissing(typeof (IProvideRecentFiles), typeof (RecentFileHistory), true);
            RegisterTypeIfMissing(typeof (IProvideFileSource), typeof (ObtainFileSource), true);
            RegisterTypeIfMissing(typeof (AppConfiguration), typeof (AppConfiguration), true);

            DoViewModelRegistrations();
        }

        void DoViewModelRegistrations()
        {
            RegisterTypeIfMissing(typeof(ShellViewModel), typeof(ShellViewModel), true);
            RegisterTypeIfMissing(typeof(MenuBarViewModel), typeof(MenuBarViewModel), true);
            RegisterTypeIfMissing(typeof(DocumentViewModel), typeof(DocumentViewModel), true);
        }
    }
}