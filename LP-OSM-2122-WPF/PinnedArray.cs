using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace LP_OSM_2122_WPF
{
    // Please, the credit goes to
    // https://stackoverflow.com/questions/50567460/how-to-return-array-of-struct-from-c-dll-to-c-sharp
    public sealed class PinnedArray<T> : IDisposable where T : struct
    {
        private GCHandle handle;
        public T[] Array { get; private set; }

        public IntPtr CreateArray(int length)
        {
            FreeHandle();
            Array = new T[length];

            try
            {

            }
            finally
            {
                handle = GCHandle.Alloc(Array, GCHandleType.Pinned);
            }

            return handle.AddrOfPinnedObject();
        }

        public IntPtr CreateArray(IntPtr length)
        {
            return CreateArray((int)length);
        }

        private void FreeHandle()
        {
            if (handle.IsAllocated)
            {
                handle.Free();
            }
        }
        public void Dispose()
        {
            FreeHandle();
        }
    }
}
