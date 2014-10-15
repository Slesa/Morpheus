using System;
using Aufgaben;

namespace Euler.fs
{
    class Program
    {
        private static readonly Aufgabe[] _aufgaben = new Aufgabe[]
            {
                new Aufgabe1()
            };
        static void Main(string[] args)
        {
            foreach (var aufgabe in _aufgaben)
            {
                Console.Write(aufgabe.Title + ": ");
                Console.WriteLine(aufgabe.Run());
            }
            Console.WriteLine("Press a key");
            Console.ReadKey();
        }
    }
}
