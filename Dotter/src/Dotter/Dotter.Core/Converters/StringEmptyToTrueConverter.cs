﻿using System;
using System.Globalization;
using System.Windows.Data;

namespace Dotter.Core.Converters
{
    public class StringEmptyToTrueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var s = value as string;
            return string.IsNullOrEmpty(s);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}