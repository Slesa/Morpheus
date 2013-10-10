using System.Collections.Generic;
using IniConfig.Editor.lib.Configuration;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Editor.specs.Configuration
{
    [Subject(typeof(AppConfiguration))]
    public class When_adding_file_to_recent_files : AppConfigurationSpecBase
    {
        Establish context = () =>
            {
                Subject.RecentFileAdded += (sender, @event) => _recentFile = @event.RecentFile;
            };

         Because of = () => Subject.UpdateRecentFiles(_fileName);

        It should_fire_added_event = () => _recentFile.FilePath.ShouldEqual(_fileName);
        It should_add_recent_file = () => RecentFiles.ShouldContainOnly(_recentFile);

        static RecentFile _recentFile;
        static string _fileName = "AnyFile";
    }

    public class AppConfigurationSpecBase : WithFakes
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