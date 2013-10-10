namespace IniConfig.Editor.lib.Configuration
{
    public interface IProvideSettings
    {
        int MaxRecentFiles { get; set; }
        string LastOpenLocation { get; set; }
    }
}