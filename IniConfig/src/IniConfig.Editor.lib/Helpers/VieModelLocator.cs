using System.Windows;
using IniConfig.Editor.lib.Contracts;
using IniConfig.Editor.lib.ViewModels;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;

namespace IniConfig.Editor.lib.Helpers
{
    public class ViewModelLocator<TRunViewModel>
        where TRunViewModel : IViewModel
    {
        readonly IUnityContainer _container;
        readonly bool _inDesignTime = System.ComponentModel.DesignerProperties.GetIsInDesignMode(new DependencyObject());

        public ViewModelLocator()
        {
            if (!_inDesignTime)
            {
                _container = ServiceLocator.Current != null ? ServiceLocator.Current.GetInstance<IUnityContainer>() : null;
            }
        }

        public IViewModel ViewModel
        {
            get
            {
                if (_inDesignTime) return null;
                return _container.Resolve<TRunViewModel>();
            }
        }
    }

    public class ShellViewModelLocator : ViewModelLocator<ShellViewModel> { }
    public class MenuBarViewModelLocator : ViewModelLocator<MenuBarViewModel> { }
    public class StatusBarViewModelLocator : ViewModelLocator<StatusBarViewModel> { }

}