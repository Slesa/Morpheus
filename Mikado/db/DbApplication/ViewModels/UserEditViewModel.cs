using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Input;
using DbApplication.Helpers;

namespace DbApplication.ViewModels
{
    public class UserEditViewModel : INotifyPropertyChanged
    {
        public EventHandler CloseMeEventHandler;
        public EventHandler<User> AddUserEventHandler;
        public EventHandler<User> EditUserEventHandler;
        private bool InEdit { get; set; }

        public UserEditViewModel()
        {
            OkCommand = new DelegateCommand(Ok, CanOk);
            CancelCommand = new DelegateCommand(Cancel);
        }

        void CloseMe()
        {
            if (CloseMeEventHandler != null) CloseMeEventHandler(this, EventArgs.Empty);
        }

        private bool CanOk(object obj)
        {
            return !string.IsNullOrEmpty(NewUserName);
        }

        private void Ok(object obj)
        {
            if (InEdit)
            {
                EditUserEventHandler?.Invoke(this, CurrentUser);
            }
            else
            {
                AddUserEventHandler?.Invoke(this, CurrentUser);
            }
            CloseMe();
        }

        public DelegateCommand OkCommand { get; set; }


        private void Cancel(object obj)
        {
            CloseMe();
        }

        public ICommand CancelCommand { get; set; }


        public string NewUserName
        {
            get { return CurrentUser.Name; }
            set { CurrentUser.Name = value; OnPropertyChanged(); OkCommand.RaiseCanExecuteChanged(); }
        }

        public string NewUserDescr
        {
            get { return CurrentUser.Description; }
            set { CurrentUser.Description = value; OnPropertyChanged(); }
        }

        private User _currentUser;
        public User CurrentUser
        {
            get { return _currentUser ?? (_currentUser = new User()); }
            set
            {
                _currentUser = value;
                InEdit = _currentUser != null;
                OnPropertyChanged("NewUserName");
                OnPropertyChanged("NewUserDescr");
            }
        }

        private Visibility _visibility;
        public Visibility Visibility
        {
            get { return _visibility; }
            set
            {
                _visibility = value;
                if (_visibility != Visibility.Visible)
                    CurrentUser = null;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}