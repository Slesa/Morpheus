using IniConfig.Console.lib.Contracts;
using IniConfig.lib;

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
        internal bool InTestMode { get; set; }
        public IIniFile IniFile { get; set; }
        public bool QuitProgram { get; set; }
    }
}