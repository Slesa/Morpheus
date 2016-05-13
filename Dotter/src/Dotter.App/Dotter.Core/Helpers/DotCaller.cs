using System.Diagnostics;
using System.IO;

namespace Dotter.App
{
    public class DotCaller
    {
        private string _tmpOutput;

        public string Run(string input)
        {
            var tmpInput = Path.Combine(Path.GetTempPath(),"dotter.in.dot"); // Path.GetTempFileName();
            File.WriteAllText(tmpInput, input);

            //if (!string.IsNullOrEmpty(_tmpOutput)) File.Delete(_tmpOutput);
            _tmpOutput = Path.Combine(Path.GetTempPath(), "dotter.out.png"); // Path.GetTempFileName() + ".png";

            // Start the child process.
            Process p = new Process();
            // Redirect the output stream of the child process.
            p.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.WorkingDirectory = "files";
            p.StartInfo.FileName = "files\\dot.exe";
            p.StartInfo.Arguments = "-Tpng " + tmpInput + " -o " + _tmpOutput;
            p.Start();
            // Do not wait for the child process to exit before
            // reading to the end of its redirected stream.
            // p.WaitForExit();
            // Read the output stream first and then wait.
            var output = p.StandardOutput.ReadToEnd();
            p.WaitForExit();

            //File.Delete(tmpInput);

            //return p.ExitCode < 0 ? string.Empty : tmpOutput;
            return _tmpOutput;
        }
    }
}