using System.Collections.Generic;
using IniConfig.Editor.lib.Configuration;
using IniConfig.Editor.lib.Helpers;
using IniConfig.Editor.lib.ViewModels;
using Machine.Fakes;
using Machine.Specifications;

namespace IniConfig.Editor.specs.ViewModels
{
    [Subject(typeof(MenuBarViewModel))]
    class When_creating_menubar_viewmodel : MenuBarViewModelSpecBase
    {
        Because of = () => _subject = new MenuBarViewModel(AppConfiguration);

        It should_have_no_active_document = () => _subject.Document.ShouldBeNull();
        It should_have_no_recent_files = () => _subject.RecentFiles.ShouldBeEmpty();

        It should_allow_new_command = () => _subject.NewCommand.CanExecute(null).ShouldBeTrue();
        It should_allow_load_command = () => _subject.LoadCommand.CanExecute(null).ShouldBeTrue();
        It should_fobid_save_command = () => _subject.SaveCommand.CanExecute(null).ShouldBeFalse();
        It should_fobid_save_as_command = () => _subject.SaveAsCommand.CanExecute(null).ShouldBeFalse();
        It should_allow_quit_command = () => _subject.QuitCommand.CanExecute(null).ShouldBeTrue();

        static MenuBarViewModel _subject;
    }


    [Subject(typeof(MenuBarViewModel))]
    class When_cancelling_loading_file_into_menubar_viewmodel : MenuBarViewModelSpecBase
    {
        Establish context = () =>
            {
                var fileSourceProvider = An<IProvideFileSource>();
                fileSourceProvider.WhenToldTo(x=>x.ObtainFileName(Param.IsAny<ObtainFileSettings>())).Return(string.Empty);

                _subject = new MenuBarViewModel(AppConfiguration) {FileSourceProvider = fileSourceProvider};
            };

        Because of = () => _subject.LoadCommand.Execute(null);

        It should_have_no_active_document = () => _subject.Document.ShouldBeNull();
        It should_have_no_recent_files = () => _subject.RecentFiles.ShouldBeEmpty();

        It should_allow_new_command = () => _subject.NewCommand.CanExecute(null).ShouldBeTrue();
        It should_allow_load_command = () => _subject.LoadCommand.CanExecute(null).ShouldBeTrue();
        It should_fobid_save_command = () => _subject.SaveCommand.CanExecute(null).ShouldBeFalse();
        It should_fobid_save_as_command = () => _subject.SaveAsCommand.CanExecute(null).ShouldBeFalse();
        It should_allow_quit_command = () => _subject.QuitCommand.CanExecute(null).ShouldBeTrue();

        static MenuBarViewModel _subject;
        const string FilePath = "file.txt";
    }


    [Subject(typeof(MenuBarViewModel))]
    class When_loading_file_into_menubar_viewmodel : MenuBarViewModelSpecBase
    {
        Establish context = () =>
            {
                var fileSourceProvider = An<IProvideFileSource>();
                fileSourceProvider.WhenToldTo(x=>x.ObtainFileName(Param.IsAny<ObtainFileSettings>())).Return(FilePath);

                _subject = new MenuBarViewModel(AppConfiguration) {FileSourceProvider = fileSourceProvider};
            };

        Because of = () => _subject.LoadCommand.Execute(null);

        It should_have_active_document = () => _subject.Document.ShouldNotBeNull();
        It should_have_document_loaded = () => _subject.Document.FilePath.ShouldEqual(FilePath);
        It should_have_recent_files = () => _subject.RecentFiles.Count.ShouldEqual(1);

        It should_allow_new_command = () => _subject.NewCommand.CanExecute(null).ShouldBeTrue();
        It should_allow_load_command = () => _subject.LoadCommand.CanExecute(null).ShouldBeTrue();
        It should_fobid_save_command = () => _subject.SaveCommand.CanExecute(null).ShouldBeFalse();
        It should_allow_save_as_command = () => _subject.SaveAsCommand.CanExecute(null).ShouldBeTrue();
        It should_allow_quit_command = () => _subject.QuitCommand.CanExecute(null).ShouldBeTrue();

        static MenuBarViewModel _subject;
        const string FilePath = "file.txt";
    }



    internal class MenuBarViewModelSpecBase : WithFakes
    {
        Establish context = () =>
            {
                RecentFiles = new List<RecentFile>();

                var recentFilesProvider = An<IProvideRecentFiles>();
                recentFilesProvider.WhenToldTo(x=>x.LoadHistory()).Return(RecentFiles);

                var settingsProvider = An<IProvideSettings>();
                settingsProvider.WhenToldTo(x=>x.MaxRecentFiles).Return(3);

                AppConfiguration = new AppConfiguration(settingsProvider, recentFilesProvider);
            };

        protected static AppConfiguration AppConfiguration;
        protected static List<RecentFile> RecentFiles;
    }
}