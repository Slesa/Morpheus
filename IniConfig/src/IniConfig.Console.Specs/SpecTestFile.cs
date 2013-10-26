using System.Collections.Generic;
using System.IO;

namespace IniConfig.Console.Specs
{
    public class SpecTestFile
    {
        public const string FileName = "SpecTest.ini";

        public static void Create()
        {
            File.WriteAllLines(FileName, Content);
        }

        public static void Remove()
        {
            File.Delete(FileName);
        }

        static IEnumerable<string> Content
        {
            get
            {
                yield return "[Settings]";
                yield return "Entry = Value";
            }
        }
    }
}