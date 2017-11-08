using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TaskRunner
{
    class Program
    {
        static void Main(string[] args)
        {
            var program = new Program();

            program.Start();
        }

        public void Start()
        {
            var t1 = RunTask();
            var t2 = RunTask();
            var t3 = RunTask();
            t1.Wait();
            t2.Wait();
            t3.Wait();
        }

        public Task RunTask()
        {
            return Task.Run(() => PerformAction());
        }

        public void PerformAction() { }
    }
}
