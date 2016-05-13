using System;
using System.Windows;
using Dotter.Core.ViewModels;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;

namespace Dotter.App
{
    public class ViewModelLocator<TViewModel> where TViewModel : class
    {
        readonly Lazy<IUnityContainer> _container;
        readonly bool _inDesignTime = System.ComponentModel.DesignerProperties.GetIsInDesignMode(new DependencyObject());

        public ViewModelLocator()
        {
            if (!_inDesignTime)
            {
                _container = new Lazy<IUnityContainer>(() => ServiceLocator.Current != null ? ServiceLocator.Current.GetInstance<IUnityContainer>() : null);
            }
        }

        public TViewModel ViewModel
        {
            get
            {
                return _inDesignTime ? null : _container.Value.Resolve<TViewModel>();
            }
        }
    }

    public class StatusbarViewModelLocator : ViewModelLocator<StatusbarViewModel> { }
    public class MenuViewModelLocator : ViewModelLocator<MenuViewModel> { }
    public class TextEditorViewModelLocator : ViewModelLocator<TextEditorViewModel> { }
    public class PreviewViewModelLocator : ViewModelLocator<PreviewViewModel> { }
}