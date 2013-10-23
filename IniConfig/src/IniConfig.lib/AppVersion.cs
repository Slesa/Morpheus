using System;
using System.Diagnostics;
using System.Reflection;

namespace IniConfig.lib
{
    public class AppVersion
    {
        public static string Version
        {
            get
            {
                var asm = Assembly.GetExecutingAssembly();
                var fvi = FileVersionInfo.GetVersionInfo(asm.Location);
                return String.Format("{0}.{1}.{2}", fvi.ProductMajorPart, fvi.ProductMinorPart, fvi.FileBuildPart);
            }
        }         
    }
}