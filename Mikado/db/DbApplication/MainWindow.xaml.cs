using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using DbApplication.ViewModels;

namespace DbApplication
{
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public MainWindow()
        {
            InitializeComponent();

            var listViewModel = _usersListView.DataContext as UsersListViewModel;
            if (listViewModel != null)
            {
                listViewModel.GotoAddEventHandler += (sender, args) => ShowAddPane();
                listViewModel.GotoEditEventHandler += (sender, args) => ShowEditPane(args);
            }

            var editViewModel = _userEditView.DataContext as UserEditViewModel;
            if (editViewModel != null)
            {
                editViewModel.AddUserEventHandler += (sender, args) => AddUser(args);
                editViewModel.EditUserEventHandler += (sender, args) => EditUser(args);
                editViewModel.CloseMeEventHandler += (sender, args) => ShowListPane();
            }
        }

        private void AddUser(User user)
        {
            var listViewModel = _usersListView.DataContext as UsersListViewModel;
            listViewModel?.AddUser(user.Name, user.Description);
        }

        private void EditUser(User user)
        {
            var listViewModel = _usersListView.DataContext as UsersListViewModel;
            listViewModel?.ChangeUser(user.Id, user.Name, user.Description);
        }

        private void ShowListPane()
        {
            _userEditView.Visibility = Visibility.Hidden;
            SetEditedUser(null);
            _usersListView.Visibility = Visibility.Visible;
        }

        private void ShowEditPane(User user)
        {
            _usersListView.Visibility = Visibility.Hidden;
            SetEditedUser(user);
            _userEditView.Visibility = Visibility.Visible;
        }

        private void SetEditedUser(User user)
        {
            var editViewModel = _userEditView.DataContext as UserEditViewModel;
            if (editViewModel != null)
            {
                editViewModel.CurrentUser = user;
            }
        }

        private void ShowAddPane()
        {
            _usersListView.Visibility = Visibility.Hidden;
            _userEditView.Visibility = Visibility.Visible;
        }



        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion INotifyPropertyChanged

        /*
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
        */
    }
}
