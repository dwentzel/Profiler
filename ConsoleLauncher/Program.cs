using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleLauncher
{
    class Program
    {
        static void Main(string[] args)
        {
            var startInfo = new ProcessStartInfo("TestApplication.exe");

            startInfo.EnvironmentVariables.Add("COR_ENABLE_PROFILING", "1");
            startInfo.EnvironmentVariables.Add("COR_PROFILER", "{43D6CE07-2262-485D-BEF3-33C0F9340C6A}");
            startInfo.EnvironmentVariables.Add("COR_PROFILER_PATH", @"c:\Users\daniel\git\Profiler\x64\Debug\ClrProfiler.dll");
            
            //startInfo.EnvironmentVariables.Add("COMPLUS_ProfAPI_ProfilerCompatibilitySetting", "EnableV2Profiler");
            //http://msdn.microsoft.com/en-us/library/ee461607.aspx

            //startInfo.EnvironmentVariables.Add("CLR_VERSION", "4");
            startInfo.UseShellExecute = false;

            Console.WriteLine("Launching process");

            var process = Process.Start(startInfo);
        }
    }
}
