//
#include "CPF/IO.hpp"
#include "CPF/IO/FileSystem.hpp"

using namespace CPF;
using namespace IO;

//////////////////////////////////////////////////////////////////////////
namespace
{
	int s_RefCount = 0;
	iFileSystem* s_pFileSystem = nullptr;
}

namespace CPF
{
	namespace IO
	{
		extern CPF_EXPORT iFileSystem* CreateFileSystem();
		extern CPF_EXPORT void DestroyFileSystem(iFileSystem*);
	}
}