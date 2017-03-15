using System;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Text;
using System.Windows.Data;

namespace DbApplication.Converters
{
    public class UsersToTextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var users = value as ObservableCollection<User>;
            if (users == null) return string.Empty;

            var sb = new StringBuilder();
            foreach (var user in users)
            {
                sb.Append("Id: ").Append(user.Id).Append(", Name: ").AppendLine(user.Name);
            }
            return sb.ToString();
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}