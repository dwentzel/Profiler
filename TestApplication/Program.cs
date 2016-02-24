using System;

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

            var string1 = "TESTSTRING FOR IntPtr";

            IntPtr ptr = System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(string1);

            while (isRunning)
            {
                string str = null;

                TestClass t = new TestClass();

                var obj = new object();

                var array = new int[10];

                var testClassArray = new TestClass[10];

                MethodWithArgs(1, 2, "testing", 2.0, 50m, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", t, ptr, out str, obj, array, testClassArray);

                if (Console.KeyAvailable)
                {
                    Console.ReadKey();
                    isRunning = false;
                }
            }
        }

        private void MethodWithArgs(
            int p1,
            int p2,
            string p3,
            double p6,
            decimal p7,
            string p8,
            TestClass testClass,
            IntPtr ptr,
            out string p9,
            object obj,
            int[] arr,
            TestClass[] testClassArray)
        {
            p9 = null;
        }
    }
}
