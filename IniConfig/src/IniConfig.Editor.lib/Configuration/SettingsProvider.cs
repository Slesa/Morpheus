using System.IO;
using IniConfig.Editor.lib.Properties;

namespace IniConfig.Editor.lib.Configuration
{
    public class SettingsProvider : IProvideSettings
    {
        readonly Settings _settings = new Settings();

        public int MaxRecentFiles
        {
            get { return _settings.MaxRecentFile; }
            set
            {
                _settings.MaxRecentFile = value;
                _settings.Save();
            }
        }

        public string LastOpenLocation
        {
            get
            {
                var lastLocation = _settings.LastLocation;
                if (string.IsNullOrEmpty(lastLocation))
                    lastLocation = Directory.GetCurrentDirectory();
                return lastLocation;
            }
            set
            {
                _settings.LastLocation = value;
                _settings.Save();
            }
        }

        public int LastFilterIndex
        {
            get { return _settings.LastFilterIndex; }
            set
            {
                _settings.LastFilterIndex = value;
                _settings.Save();
            }
        }
    }
}