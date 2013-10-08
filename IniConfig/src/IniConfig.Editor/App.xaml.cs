using System.Windows;

namespace IniConfig.Editor
{
    public partial class App : Application
    {
        private void OnApplicationStartup(object sender, StartupEventArgs e)
        {
            var bootstrapper = new Bootstrapper();
            bootstrapper.Run();
        }
    }
}
