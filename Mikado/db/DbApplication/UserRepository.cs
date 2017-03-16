﻿using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.IO;

namespace DbApplication
{
    public class UserRepository
    {
        string dataSource = "SQLiteDemo.db";

        private SQLiteConnection Connection { get; set; }

        private SQLiteConnection OpenDatabase()
        {
            SQLiteConnection connection = new SQLiteConnection();

            connection.ConnectionString = "Data Source=" + dataSource;
            connection.Open();
            return connection;
        }

        public IEnumerable<User> FindAll()
        {
            using (var command = new SQLiteCommand(Connection))
            {
                // Auslesen des zuletzt eingefügten Datensatzes.
                command.CommandText = "SELECT id, name, descr FROM users";

                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        var id = reader.GetInt64(0);
                        var user = new User() { Id = id, Name = reader[1].ToString(), Description = reader[2].ToString() };
                        yield return user;
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

        public void Create(string name, string descr)
        {
            using (SQLiteCommand command = new SQLiteCommand(Connection))
            {
                command.CommandText = string.Format("INSERT INTO users (name, descr) VALUES('{0}', '{1}')", name, descr);
                command.ExecuteNonQuery();
            }
        }

        public void Update(long id, string name, string descr)
        {
            using (SQLiteCommand command = new SQLiteCommand(Connection))
            {
                command.CommandText = "UPDATE users set name = :name, descr = :descr where id=:id";
                command.Parameters.Add("name", DbType.String).Value = name;
                command.Parameters.Add("descr", DbType.String).Value = descr;
                command.Parameters.Add("id", DbType.Int64).Value = id;
                command.ExecuteNonQuery();
            }
        }

        public void CreateDemoDataIfNecessary()
        {
            var createDemo = !File.Exists(dataSource);
            Connection = OpenDatabase();
            if (createDemo)
                CreateDemoData();
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
    }
}