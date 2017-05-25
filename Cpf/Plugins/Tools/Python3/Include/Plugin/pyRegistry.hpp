//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Python.h>
#include "GOM/pyBase.hpp"

namespace Cpf
{
	namespace Plugin
	{
		namespace py
		{
			struct Registry
			{
				GOM::py::Base mBase;
			};
			extern PyTypeObject PluginRegistry_type;

			bool AddRegistryType(PyObject* parent);
		}
	}
}
