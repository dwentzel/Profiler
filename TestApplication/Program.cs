using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestApplication
{
    class Program
    {
        static void Main(string[] args)
        {
            Program program = new Program();
            program.Run();
        }

        private void Run()
        {
            bool isRunning = true;

            Console.WriteLine("Running, press any key to quit...");

            while (isRunning)
            {
                Method8Args(1, 2, "testing", "argxx", "voodoo", 2.0, 50m, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

                if (Console.KeyAvailable)
                {
                    Console.ReadKey();
                    isRunning = false;
                }
            }

            Console.ReadKey();
        }

        private void Method8Args(int p1, int p2, string p3, string p4, string p5, double p6, decimal p7, string p8)
        {
            
        }
    }
}
