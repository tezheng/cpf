using System;
using System.Runtime.InteropServices;
namespace CPF
{
    namespace Plugin
    {
        [StructLayout(LayoutKind.Sequential)]
        public class iClassInstanceVTable : iUnknownVTable
        {
            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate UInt32 CreateInstanceFunc(IntPtr self, IntPtr registry, IntPtr outer, out IntPtr outInstance);            
            
            [MarshalAs(UnmanagedType.FunctionPtr)]
            public CreateInstanceFunc CreateInstance;

        }
        public interface iClassInstance
        {
            UInt32 CreateInstance(IntPtr self, IntPtr registry, IntPtr outer, out IntPtr outInstance);            
        }
        public class iClassInstanceWrapper : IWrapper
        {
            private IntPtr unmanagedInstance;
            private iClassInstance instance;
            private iClassInstanceVTable vTable = new iClassInstanceVTable();
            private GenericObject genericObject = new GenericObject();

            public IntPtr NativePointer => unmanagedInstance;
            public UInt64 CID => 0x46BA0E3ACD49505F;

            public iClassInstanceWrapper(IntPtr unmanagedInst)
            {
                unmanagedInstance = unmanagedInst;
                Marshal.PtrToStructure(unmanagedInst, genericObject);
                Marshal.PtrToStructure(genericObject.VTablePtr, vTable);
            }

            public iClassInstanceWrapper(iClassInstance inst)
            {
                instance = inst;
                var unknown = (IUnknown)inst;
                
                vTable.AddRef = unknown.AddRef;
                vTable.Release = unknown.Release;
                vTable.QueryInterface = unknown.QueryInterface;
                vTable.CreateInstance = inst.CreateInstance;
                genericObject.VTablePtr = Marshal.AllocHGlobal(Marshal.SizeOf(vTable));
                unmanagedInstance = Marshal.AllocHGlobal(Marshal.SizeOf(genericObject));
                Marshal.StructureToPtr(vTable, genericObject.VTablePtr, false);
                Marshal.StructureToPtr(genericObject, unmanagedInstance, false);
            }

            public UInt32 CreateInstance(IntPtr registry, IntPtr outer, out IntPtr outInstance)
            {
                 return vTable.CreateInstance(unmanagedInstance, registry, outer, out outInstance);
            }
        }
    }
}
