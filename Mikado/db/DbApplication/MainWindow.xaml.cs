using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Data.SQLite;
using System.IO;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;

namespace DbApplication
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private string _newUserName;
        private string _newUserDescr;
        private UserRepository _userRepository;

        public ObservableCollection<User> Users { get; private set; }

        public string NewUserName
        {
            get { return _newUserName; }
            set { _newUserName = value; OnPropertyChanged(); }
        }

        public string NewUserDescr
        {
            get { return _newUserDescr; }
            set { _newUserDescr = value; OnPropertyChanged(); }
        }

        public long EditUserId { get; set; }
        private bool InEdit { get; set; }

        public MainWindow()
        {
            Users = new ObservableCollection<User>();
            _userRepository = new UserRepository();
            InitializeComponent();
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            _userRepository.CreateDemoDataIfNecessary();
            ReadUsers();
        }

        private void ReadUsers()
        {
            Users.Clear();
            var users = _userRepository.FindAll();
            foreach(var user in users)
                Users.Add(user);
        }


        void AddUser(string name, string descr)
        {
            _userRepository.Create(name, descr);
            ReadUsers();
        }

        void ChangeUser(long id, string name, string descr)
        {
            _userRepository.Update(id, name, descr);
            ReadUsers();
        }

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion INotifyPropertyChanged

        private void ButtonBase_OnAdd(object sender, RoutedEventArgs e)
        {
            NewUserName = string.Empty;
            NewUserDescr = string.Empty;
            InEdit = false;

            _listDock.Visibility = Visibility.Hidden;
            _inputDock.Visibility = Visibility.Visible;
        }

        private void ButtonBase_OnEdit(object sender, RoutedEventArgs e)
        {
            var user = _listUsers.SelectedValue as User;
            if (user == null)
            {
                MessageBox.Show(this, "No user selected", "Error");
                return;
            }

            NewUserName = user.Name;
            NewUserDescr = user.Description;
            EditUserId = user.Id;
            InEdit = true;

            _listDock.Visibility = Visibility.Hidden;
            _inputDock.Visibility = Visibility.Visible;
        }

        private void ButtonBase_OnOk(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(NewUserName))
            {
                MessageBox.Show(this, "User name cannot be empty", "Error");
                return;
            }


            if (InEdit)
                ChangeUser(EditUserId, NewUserName, NewUserDescr);
            else
                AddUser(NewUserName, NewUserDescr);

            ButtonBase_OnCancel(sender, e);
        }

        private void ButtonBase_OnCancel(object sender, RoutedEventArgs e)
        {
            _listDock.Visibility = Visibility.Visible;
            _inputDock.Visibility = Visibility.Hidden;
        }
    }
}
