﻿using System;

namespace ComTest
{
	public class MyClassInstance : Unknown, iClassInstance
	{
		public override int QueryInterface(IntPtr self, ulong id, IntPtr outInterface)
		{
			return base.QueryInterface(self, id, outInterface);
		}

		public uint CreateInstance(IntPtr self, IntPtr registry, iUnknown outer, out IntPtr outInstance)
		{
			var testPlugin = new TestPlugin(outer);

			outInstance = Plugin.CustomMarshal(testPlugin);
			ReferenceStorage.Add(outInstance);

			return 0x7b48e63f;
		}
	}
}