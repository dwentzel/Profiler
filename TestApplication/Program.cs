using System;
using System.Runtime.InteropServices;

namespace TestApplication
{
    class TestClass
    {

    }

    class Program
    {
        ////#region Trap application termination
        ////[DllImport("Kernel32")]
        ////private static extern bool SetConsoleCtrlHandler(EventHandler handler, bool add);

        ////private delegate bool EventHandler(CtrlType sig);
        ////static EventHandler _handler;

        ////enum CtrlType
        ////{
        ////    CTRL_C_EVENT = 0,
        ////    CTRL_BREAK_EVENT = 1,
        ////    CTRL_CLOSE_EVENT = 2,
        ////    CTRL_LOGOFF_EVENT = 5,
        ////    CTRL_SHUTDOWN_EVENT = 6
        ////}

        ////private static bool Handler(CtrlType sig)
        ////{
        ////    Console.WriteLine("Exiting system due to external CTRL-C, or process kill, or shutdown");
        ////    Environment.Exit(-1);

        ////    return true;
        ////}
        ////#endregion

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

            TestApplicationIL.TestClass1 x;

            Console.WriteLine("TestApplication stopped");
            Console.ReadKey();
        }

        private void Run()
        {
            bool isRunning = true;

            Console.WriteLine("Running, press CTRL-C to quit...");

            var string1 = "TESTSTRING FOR IntPtr";

            IntPtr intPtrToString = Marshal.StringToHGlobalAnsi(string1);

            while (isRunning)
            {
                string outString = null;

                TestClass testClass = new TestClass();

                var obj = new object();

                var intArray = new int[10];

                var testClassArray = new TestClass[10];

                var twoDimensionalStringArray = new string[10][];

                MethodWithArgs(
                    1,
                    2,
                    "testing",
                    2.0,
                    50m,
                    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                    testClass,
                    intPtrToString,
                    out outString,
                    obj,
                    intArray,
                    testClassArray,
                    twoDimensionalStringArray);
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
            TestClass[] testClassArray,
            string[][] twoDimensionalStringArray)
        {
            p9 = null;
        }
    }
}
