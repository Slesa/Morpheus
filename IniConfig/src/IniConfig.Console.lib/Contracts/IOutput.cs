namespace IniConfig.Console.lib.Contracts
{
    public interface IOutput
    {
        IOutput WriteLine(string text = "");
        IOutput Write(string text);
    }
}