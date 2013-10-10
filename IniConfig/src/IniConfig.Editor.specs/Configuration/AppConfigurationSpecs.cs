using System.Collections.Generic;
using IniConfig.Editor.lib.Configuration;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Editor.specs.Configuration
{
    [Subject(typeof(AppConfiguration))]
    internal class When_adding_file_to_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _recentFile = @event.RecentFile;
            };

         Because of = () => Subject.UpdateRecentFiles(FileName);

        It should_fire_added_event = () => _recentFile.FilePath.ShouldEqual(FileName);
        It should_add_recent_file = () => RecentFiles.ShouldContainOnly(_recentFile);

        static RecentFile _recentFile;
        const string FileName = "AnyFile";
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_removing_recent_file_not_in_list : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileRemoved += (sender, @event) => _removedFile = @event.RecentFile;
            };

        Because of = () => Subject.RemoveRecentFile(FileName);

        It should_not_fire_removed_event = () => _removedFile.ShouldBeNull();
        It should_not_add_file_to_list = () => RecentFiles.ShouldBeEmpty();

        const string FileName = "AnyFile";
        static RecentFile _removedFile;
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_removing_file_from_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileRemoved += (sender, @event) => _removedFile = @event.RecentFile;
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    var name = FileName + "-" + i;
                    RecentFiles.Add(new RecentFile { Name = name, FilePath = name });
                }
                _removedFileName = FileName + "-" + Settings.MaxRecentFiles/2;
            };

        Because of = () => Subject.RemoveRecentFile(_removedFileName);

        It should_fire_removed_event = () => _removedFile.FilePath.ShouldEqual(_removedFileName);
        It should_keep_other_recent_files = () => RecentFiles.Count.ShouldEqual(Settings.MaxRecentFiles-1);

        It should_keep_order = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles/2; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + i);
                }
                for (var i = Settings.MaxRecentFiles/2+1; i < Settings.MaxRecentFiles-1; i++)
                {
                    RecentFiles[i-1].FilePath.ShouldEqual(FileName + "-" + i);
                }
            };

        static List<RecentFile> _addedFiles = new List<RecentFile>();
        static RecentFile _removedFile;
        const string FileName = "AnyFile";
        static string _removedFileName;
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_adding_file_maximum_number_to_recent_files : AppConfigurationSpecBase
    {
        private Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _addedFiles.Add(@event.RecentFile);
            };

        Because of = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    Subject.UpdateRecentFiles(FileName + "-" + i);
                }
            };

        It should_fire_all_added_events = () => _addedFiles.Count.ShouldEqual(Settings.MaxRecentFiles);
        It should_add_recent_files = () => RecentFiles.Count.ShouldEqual(Settings.MaxRecentFiles);
        It should_add_in_the_right_order = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + i);
                }
            };

        static readonly List<RecentFile> _addedFiles = new List<RecentFile>();
        const string FileName = "AnyFile";
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_adding_more_files_than_maximum_to_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _addedFiles.Add(@event.RecentFile);
                Subject.RecentFileRemoved += (sender, @event) => _removedFile = @event.RecentFile;
            };

        Because of = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles+1; i++)
                {
                    Subject.UpdateRecentFiles(FileName + "-" + i);
                }
            };

        It should_fire_all_added_events = () => _addedFiles.Count.ShouldEqual(Settings.MaxRecentFiles+1);
        It should_fire_removed_event = () => _removedFile.ShouldNotBeNull();
        It should_fill_recent_files = () => RecentFiles.Count.ShouldEqual(Settings.MaxRecentFiles);
        It should_remove_last_recent_file = () => _removedFile.FilePath.ShouldEqual(FileName+"-0");
        It should_add_in_the_right_order = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + (i+1));
                }
            };

        static readonly List<RecentFile> _addedFiles = new List<RecentFile>();
        static RecentFile _removedFile;
        const string FileName = "AnyFile";
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_re_adding_last_file_of_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _addedFile = @event.RecentFile;
                Subject.RecentFileRemoved += (sender, @event) => _removedFile = @event.RecentFile;
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    var name = FileName + "-" + i;
                    RecentFiles.Add(new RecentFile {Name = name, FilePath = name});
                }
            };

        Because of = () => Subject.UpdateRecentFiles(FileName + "-" + (Settings.MaxRecentFiles-1));

        It should_not_fire_added_event = () => _addedFile.ShouldBeNull();
        It should_not_fire_removed_event = () => _removedFile.ShouldBeNull();
        It should_keep_recent_files = () => RecentFiles.Count.ShouldEqual(Settings.MaxRecentFiles);
        It should_keep_the_order = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + i);
                }
            };

        static RecentFile _addedFile;
        static RecentFile _removedFile;
        const string FileName = "AnyFile";
    }


    [Subject(typeof(AppConfiguration))]
    internal class When_re_adding_any_file_of_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _addedFiles.Add(@event.RecentFile);
                Subject.RecentFileRemoved += (sender, @event) => _removedFile = @event.RecentFile;
                for (var i = 0; i < Settings.MaxRecentFiles; i++)
                {
                    var name = FileName + "-" + i;
                    RecentFiles.Add(new RecentFile {Name = name, FilePath = name});
                }
                _readdedFileName = FileName + "-" + (Settings.MaxRecentFiles/2);
            };

        Because of = () => Subject.UpdateRecentFiles(_readdedFileName);

        It should_fire_added_event = () => _addedFiles.Count.ShouldEqual(1);
        It should_fire_removed_event = () => _removedFile.FilePath.ShouldEqual(_readdedFileName);
        It should_keep_recent_files = () => RecentFiles.Count.ShouldEqual(Settings.MaxRecentFiles);
        It should_put_readded_file_in_front = () => RecentFiles[Settings.MaxRecentFiles-1].FilePath.ShouldEqual(_readdedFileName);
        It should_keep_the_order = () =>
            {
                for (var i = 0; i < Settings.MaxRecentFiles/2; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + (i));
                }
                for (var i = Settings.MaxRecentFiles / 2; i < Settings.MaxRecentFiles-1; i++)
                {
                    RecentFiles[i].FilePath.ShouldEqual(FileName + "-" + (i+1));
                }
            };

        static readonly List<RecentFile> _addedFiles = new List<RecentFile>();
        static RecentFile _removedFile;
        const string FileName = "AnyFile";
        static string _readdedFileName;
    }



    internal class AppConfigurationSpecBase : WithFakes
    {
        private Establish context = () =>
            {
                RecentFiles = new List<RecentFile>();
                Settings = An<IProvideSettings>();
                Settings.WhenToldTo(x=>x.MaxRecentFiles).Return(3);
                History = An<IProvideRecentFiles>();
                History.WhenToldTo(x=>x.LoadHistory()).Return(RecentFiles);
                Subject = new AppConfiguration(Settings, History);
            };

        protected static List<RecentFile> RecentFiles;
        protected static IProvideSettings Settings;
        protected static IProvideRecentFiles History;
        protected static AppConfiguration Subject;
    }
}