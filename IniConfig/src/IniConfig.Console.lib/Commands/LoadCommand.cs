﻿using System.Collections.Generic;
using System.IO;
using System.Linq;
using IniConfig.Console.lib.Contracts;
using IniConfig.Console.lib.Extensions;
using IniConfig.Console.lib.Resources;
using IniConfig.lib;

namespace IniConfig.Console.lib.Commands
{
    public class LoadCommand : IMenuCommand
    {
        public LoadCommand()
        {
            Shortcut = "l";
            Description = Strings.LoadCommand_Description;
        }

        public string Shortcut { get; private set; }
        public string Description { get; private set; }

        public List<string> Execute(List<string> nextToken, AppEnvironment environment)
        {
            var fileName = nextToken.Head();
            var result = nextToken.Tail().ToList();
            
            if (environment.InTestMode && fileName == "q")
            {
                result.Add(fileName);
                fileName = string.Empty;
            }

            if (string.IsNullOrEmpty(fileName))
            {
                environment.Out.WriteLine(Strings.Warning_NoFilenameGiven);
                return result;
            }

            try
            {
                var inifile = IniFile.LoadFrom(fileName);
                environment.IniFile = inifile;
            }
            catch (FileNotFoundException)
            {
                environment.Out.WriteLine(Strings.Error_FileNotFound);
                return result;
            }
            catch (DirectoryNotFoundException)
            {
                environment.Out.WriteLine(Strings.Error_DirectoryNotFound);
                return result;
            }
            return result;
        }
    }
}