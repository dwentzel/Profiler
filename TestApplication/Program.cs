﻿using System;

namespace TestApplication
{
    class TestClass
    {

    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Program program = new Program();
                program.Run();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }

            Console.WriteLine("TestApplication stopped");
            Console.ReadKey();
        }

        private void Run()
        {
            bool isRunning = true;

            Console.WriteLine("Running, press any key to quit...");

            IntPtr ptr = IntPtr.Zero;

            while (isRunning)
            {
                string str = null;

                TestClass t = new TestClass();

                Method8Args(1, 2, "testing", 2.0, 50m, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", t, ptr, out str);

                if (Console.KeyAvailable)
                {
                    Console.ReadKey();
                    isRunning = false;
                }
            }
        }

        private void Method8Args(int p1, int p2, string p3, double p6, decimal p7, string p8, TestClass t, IntPtr ptr, out string p9)
        {
            p9 = null;
        }
    }
}
