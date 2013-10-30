using System;
using System.Collections.Generic;
using System.IO;

namespace IniConfig.Console.Specs
{
    public class SpecTestFile
    {
      public SpecTestFile(Type specTest)
      {
        FileName = "Spec." + specTest.Name + ".ini";
      }

        public string FileName { get; private set; }

        public void Create()
        {
            File.WriteAllLines(FileName, Content);
        }

        public void Remove()
        {
            File.Delete(FileName);
        }

        static IEnumerable<string> Content
        {
            get
            {
                yield return "[Log]";
                yield return "Level = All";
                yield return "MaxSize = 512";
                yield return "File = myapplication.log";
                yield return "";
                yield return "[Settings]";
                yield return "Entry = Value";
            }
        }
    }
}