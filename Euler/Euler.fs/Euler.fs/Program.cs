using System;
using System.Diagnostics;
using Aufgaben;

namespace Euler.fs
{
    class Program
    {
        private static readonly Aufgabe[] _aufgaben = new Aufgabe[]
            {
                new Aufgabe1(),
                new Aufgabe2(),
                new Aufgabe3(),
                new Aufgabe4(),
                new Aufgabe6(),
                //new Aufgabe7(), // too long 2,5s
                //new Aufgabe10(), // 215s
                new Aufgabe17(), 
                new Aufgabe31(), 
            };
        static void Main(string[] args)
        {
            var sw = new Stopwatch();

            foreach (var aufgabe in _aufgaben)
            {
                Console.Write(aufgabe.Title + ": ");
                sw.Restart();
                var result = aufgabe.Run();
                var dist = sw.ElapsedMilliseconds;
                Console.WriteLine(string.Format("{0} ({1} ms)", result, dist));
            }
            Console.WriteLine("Press a key");
            Console.ReadKey();
        }
    }
}
