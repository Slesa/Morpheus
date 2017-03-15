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
        string dataSource = "SQLiteDemo.db";
        private string _newUserName;
        private string _newUserDescr;

        private SQLiteConnection Connection { get; set; }
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
            InitializeComponent();
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            var createDemo = !File.Exists(dataSource);
            Connection = OpenDatabase();
            if (createDemo)
                CreateDemoData();
            ReadUsers();
        }

        private SQLiteConnection OpenDatabase()
        {
            SQLiteConnection connection = new SQLiteConnection();

            connection.ConnectionString = "Data Source=" + dataSource;
            connection.Open();
            return connection;
        }

        private void ReadUsers()
        {
            Users.Clear();
            using (var command = new SQLiteCommand(Connection))
            {
                // Auslesen des zuletzt eingefügten Datensatzes.
                command.CommandText = "SELECT id, name, descr FROM users";

                using (var reader = command.ExecuteReader())
                {

                    while (reader.Read())
                    {
                        var id = reader.GetInt64(0);
                        var user = new User() {Id = id, Name = reader[1].ToString(), Description = reader[2].ToString()};
                        Users.Add(user);
                    }

                    // Beenden des Readers und Freigabe aller Ressourcen.
                    reader.Close();
                }
            }
            /* using (var command = new SQLiteCommand(Connection))
            {
                command.CommandText = "SELECT COUNT(id) FROM users";
                command.CommandType = CommandType.Text;
                UserCount = Convert.ToInt32(command.ExecuteScalar());
            } */
        }

        private void CreateDemoData()
        {
            using (SQLiteCommand command = new SQLiteCommand(Connection))
            {
                // Erstellen der Tabelle, sofern diese noch nicht existiert.
                command.CommandText =
                    "CREATE TABLE IF NOT EXISTS users ( id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(100) NOT NULL, descr VARCHAR(256));";
                command.ExecuteNonQuery();

                // Einfügen eines Test-Datensatzes.
                command.CommandText = "INSERT INTO users (name) VALUES('Captain Picard')";
                command.ExecuteNonQuery();
                command.CommandText = "INSERT INTO users (name) VALUES('Lt Commander Riker')";
                command.ExecuteNonQuery();
                command.CommandText = "INSERT INTO users (name) VALUES('Lt Worf')";
                command.ExecuteNonQuery();
            }
        }

        void AddUser(string name, string descr)
        {
            using (SQLiteCommand command = new SQLiteCommand(Connection))
            {
                command.CommandText = string.Format("INSERT INTO users (name, descr) VALUES('{0}', '{1}')", name, descr);
                command.ExecuteNonQuery();
            }
            ReadUsers();
        }

        void ChangeUser(long id, string name, string descr)
        {
            using (SQLiteCommand command = new SQLiteCommand(Connection))
            {
                command.CommandText = "UPDATE users set name = :name, descr = :descr where id=:id";
                command.Parameters.Add("name", DbType.String).Value = name;
                command.Parameters.Add("descr", DbType.String).Value = descr;
                command.Parameters.Add("id", DbType.Int64).Value = id;
                command.ExecuteNonQuery();
            }
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
