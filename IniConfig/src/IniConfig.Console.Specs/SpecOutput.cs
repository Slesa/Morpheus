using IniConfig.Console.lib.Contracts;

namespace IniConfig.Console.Specs
{
    class SpecOutput : IOutput
    {
        public SpecOutput()
        {
            Buffer = string.Empty;
        }

        public IOutput WriteLine(string text)
        {
            Buffer += text + "\n";
            return this;
        }

        public IOutput Write(string text)
        {
            Buffer += text;
            return this;
        }

        public string Buffer { get; set; }
    }
}