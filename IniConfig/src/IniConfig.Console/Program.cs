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
        public void WriteLine(string text)
        {
            System.Console.WriteLine(text);
        }

        public void Write(string text)
        {
            System.Console.Write(text);
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
