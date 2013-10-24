using IniConfig.Console.lib.Contracts;

namespace IniConfig.Console.lib
{
    public class AppEnvironment
    {
        public AppEnvironment(IInput input, IOutput output)
        {
            In = input;
            Out = output;
        }

        public IInput In { get; set; }
        public IOutput Out { get; set; }
        public string FileName { get; set; }
        internal bool InTestMode { get; set; }
    }
}