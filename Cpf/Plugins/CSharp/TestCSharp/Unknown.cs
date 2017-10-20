﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace ComTest
{
	public interface IWrapper
	{
		UInt64 CID { get; }
		IntPtr NativePointer { get; }
	}

	public class Unknown : IUnknown
	{
		private int refCount;
		private Dictionary<UInt64, IWrapper> wrappers = new Dictionary<UInt64, IWrapper>();
		private Dictionary<Type, IWrapper> wrappersByType = new Dictionary<Type, IWrapper>();

		public Unknown()
		{
			refCount = 1;
			ReferenceStorage.Add(this);
		}

		public int AddRef(IntPtr self)
		{
			return ++refCount;
		}

		public int Release(IntPtr self)
		{
			--refCount;

			if(refCount == 0)
			{
				ReferenceStorage.Remove(this);
			}

			return refCount;
		}

		public int QueryInterface(IntPtr self, ulong id, IntPtr outInterface)
		{
			if(id == 123456789)
			{
				Marshal.WriteIntPtr(outInterface, wrappers.First().Value.NativePointer);
				return 1;
			}
			
			if(wrappers.TryGetValue(id, out var wrapper))
			{
				Marshal.WriteIntPtr(outInterface, wrapper.NativePointer);
				return 1;
			}
			
			return 0;
		}

		public IntPtr QueryInterface<T>()
		{
			return wrappersByType[typeof(T)].NativePointer;
		}

		protected void AddWrapper(IWrapper wrapper)
		{
			wrappers.Add(wrapper.CID, wrapper);
			wrappersByType.Add(wrapper.GetType(), wrapper);
		}
	}
}