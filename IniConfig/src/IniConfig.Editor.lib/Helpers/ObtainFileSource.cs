using System.IO;
using Microsoft.Win32;

namespace IniConfig.Editor.lib.Helpers
{
    public class ObtainFileSource : IProvideFileSource
    {
        public string ObtainFileName(ObtainFileSettings settings)
        {
            var openFile = new OpenFileDialog
                {
                    Filter = settings.FileFilter,
                    FilterIndex = settings.FileFilterIndex,
                    Title = settings.DialogTitle,
                    InitialDirectory = settings.LastLocation,
                    CheckFileExists = true,
                    Multiselect = false
                };

            //openFile.RestoreDirectory = false;

            IsCurrentlyObtaining = true;
            var result = openFile.ShowDialog();
            IsCurrentlyObtaining = false;

            if (result == false) return string.Empty; //Warning, nullable

            var fileName = openFile.FileName;
            var fileInfo = new FileInfo(fileName);
            if (fileInfo.Directory != null) settings.LastLocation = fileInfo.Directory.FullName;
            settings.FileFilterIndex = openFile.FilterIndex;

            return fileName;
        }

        public bool IsCurrentlyObtaining { get; private set; }
    }
}