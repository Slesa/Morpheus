﻿//      *********    DO NOT MODIFY THIS FILE     *********
//      This file is regenerated by a design tool. Making
//      changes to this file can cause errors.
namespace Expression.Blend.SampleData.RecentFilesDataSource
{
	using System; 

// To significantly reduce the sample data footprint in your production application, you can set
// the DISABLE_SAMPLE_DATA conditional compilation constant and disable sample data at runtime.
#if DISABLE_SAMPLE_DATA
	internal class RecentFilesDataSource { }
#else

	public class RecentFilesDataSource : System.ComponentModel.INotifyPropertyChanged
	{
		public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

		protected virtual void OnPropertyChanged(string propertyName)
		{
			if (this.PropertyChanged != null)
			{
				this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
			}
		}

		public RecentFilesDataSource()
		{
			try
			{
				System.Uri resourceUri = new System.Uri("/IniConfig.Editor.Screens;component/SampleData/RecentFilesDataSource/RecentFilesDataSource.xaml", System.UriKind.Relative);
				if (System.Windows.Application.GetResourceStream(resourceUri) != null)
				{
					System.Windows.Application.LoadComponent(this, resourceUri);
				}
			}
			catch (System.Exception)
			{
			}
		}

		private RecentFiles _RecentFiles = new RecentFiles();

		public RecentFiles RecentFiles
		{
			get
			{
				return this._RecentFiles;
			}
		}
	}

	public class RecentFilesItem : System.ComponentModel.INotifyPropertyChanged
	{
		public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

		protected virtual void OnPropertyChanged(string propertyName)
		{
			if (this.PropertyChanged != null)
			{
				this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
			}
		}

		private string _Name = string.Empty;

		public string Name
		{
			get
			{
				return this._Name;
			}

			set
			{
				if (this._Name != value)
				{
					this._Name = value;
					this.OnPropertyChanged("Name");
				}
			}
		}

		private string _FilePath = string.Empty;

		public string FilePath
		{
			get
			{
				return this._FilePath;
			}

			set
			{
				if (this._FilePath != value)
				{
					this._FilePath = value;
					this.OnPropertyChanged("FilePath");
				}
			}
		}
	}

	public class RecentFiles : System.Collections.ObjectModel.ObservableCollection<RecentFilesItem>
	{ 
	}
#endif
}
