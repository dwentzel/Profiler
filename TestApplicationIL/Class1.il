.assembly extern mscorlib {}
.assembly TestApplicationIL 
{
    .ver 0:0:0:1
}
.module TestApplicationIL.dll

.namespace TestApplicationIL
{

    .class public ansi auto TestClass1 extends [mscorlib]System.Object
    {
        .method public specialname rtspecialname instance void .ctor() cil managed
        {
            ldarg.0
            call instance void [mscorlib]System.Object::.ctor()
            ret
        }

        .method public instance void PrintTest() cil managed
        {
            .maxstack 1
            
            ldstr "TestApplicationIL.TestClass1.PrintTest()"
            call void [mscorlib]System.Console::WriteLine(string)

            ret
        }
    }

}