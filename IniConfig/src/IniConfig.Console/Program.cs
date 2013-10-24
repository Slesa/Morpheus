using IniConfig.Console.lib;
using IniConfig.Console.lib.Contracts;

namespace IniConfig.Console
{
    class ConsoleInput : IInput
    {
        public string ReadLine()
        {
            return System.Console.ReadLine();
        }
    }

    class ConsoleOutput : IOutput
    {
        public IOutput WriteLine(string text)
        {
            System.Console.WriteLine(text);
            return this;
        }

        public IOutput Write(string text)
        {
            System.Console.Write(text);
            return this;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var mainMenu = new MainMenu(new ConsoleInput(), new ConsoleOutput());
            mainMenu.Run();
        }
    }
}
