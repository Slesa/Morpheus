namespace IniConfig.Editor.lib.Helpers
{
    public interface IProvideFileSource
    {
        string ObtainFileName(ObtainFileSettings settings);
        string ObtainFileSaveName(ObtainFileSettings settings);
        bool IsCurrentlyObtaining { get; }
    }
}