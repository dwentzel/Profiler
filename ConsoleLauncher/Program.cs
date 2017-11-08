using System;
using System.Diagnostics;
using System.IO;

namespace ConsoleLauncher
{
    class Program
    {
        static void Main(string[] args)
        {
            var startInfo = new ProcessStartInfo("TaskRunner.exe");

            startInfo.EnvironmentVariables.Add("COR_ENABLE_PROFILING", "1");
            startInfo.EnvironmentVariables.Add("COR_PROFILER", "{710abc47-aa19-407f-84fb-48c12f6307ed}");
            //startInfo.EnvironmentVariables.Add("COR_PROFILER", "DotNetProfiler");

            var currentDirectory = Directory.GetCurrentDirectory();

            var profilerPath = IntPtr.Size == 4 ?
                Path.Combine("..", "..", "..", "..", "Debug", "DotNetProfiler.dll"):
                Path.Combine("..", "..", "..", "..", "x64", "Debug", "DotNetProfiler.dll");

            var fileInfo = new FileInfo(profilerPath);

            Console.WriteLine("Profiler path: {0}", fileInfo.FullName);
            ////throw new Exception(profilerPath);
            startInfo.EnvironmentVariables.Add("COR_PROFILER_PATH", fileInfo.FullName);

            //startInfo.EnvironmentVariables.Add("COMPLUS_ProfAPI_ProfilerCompatibilitySetting", "EnableV2Profiler");
            //http://msdn.microsoft.com/en-us/library/ee461607.aspx

            //startInfo.EnvironmentVariables.Add("CLR_VERSION", "4");
            startInfo.UseShellExecute = false;

            Console.WriteLine("Launching process");
            var process = Process.Start(startInfo);

            process.WaitForExit();
            Console.WriteLine("\n\n\nProgram execution finished. Press any key to exit Launcher");
            Console.ReadKey();
        }
    }
}
