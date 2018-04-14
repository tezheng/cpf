//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration/Setup.hpp"

//////////////////////////////////////////////////////////////////////////
#if CPF_TARGET_WINDOWS
#	ifndef NOCOMM
#		define NOCOMM
#	endif
#	ifndef STRICT
#		define STRICT
#	endif
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <WinSock2.h>
#	include <Windows.h>
// Windows.h needs a fricken "don't use shitty macro's" flag....
#	undef CreateWindow

#	define CPF_DLL_SAFE_BEGIN __pragma(warning(push)) __pragma(warning(disable:4251))
#	define CPF_DLL_SAFE_END __pragma(warning(pop))
#	define CPF_CDECL __cdecl
#	define CPF_STDCALL __stdcall
#	define CPF_VECTORCALL __vectorcall
#	define CPF_NOVTABLE __declspec(novtable)
#	define CPF_FORCE_INLINE __forceinline
#	define CPF_DEBUG_BREAK ::DebugBreak()
#	define CPF_ALIGN(size) alignas(size)
#	define CPF_IMPORT_ATTR __declspec(dllimport)
#	define CPF_EXPORT_ATTR __declspec(dllexport)

#	ifdef CPF_TARGET_WINDOWS
#		ifdef CPF_STATIC
#			define CPF_EXPORT
#		else // CPF_STATIC
#			if CPF_BUILD
#				define CPF_EXPORT CPF_EXPORT_ATTR
#			else
#				define CPF_EXPORT CPF_IMPORT_ATTR
#			endif
#		endif
#	else // CPF_TARGET_WINDOWS
#		define CPF_EXPORT CPF_EXPORT_ATTR
#	endif // CPF_TARGET_WINDOWS

//////////////////////////////////////////////////////////////////////////
#elif CPF_TARGET_DARWIN
#	define	CPF_ALIGN( size ) alignas(size)

//////////////////////////////////////////////////////////////////////////
#elif CPF_TARGET_LINUX

//////////////////////////////////////////////////////////////////////////
#elif CPF_TARGET_IOS
#	define	CPF_ALIGN( size ) alignas(size)

//////////////////////////////////////////////////////////////////////////
#elif CPF_TARGET_ANDROID
#endif

//////////////////////////////////////////////////////////////////////////
#define _CPF_STRINGIZE(a) #a
#define CPF_STRINGIZE(a) _CPF_STRINGIZE(a)
#define _CPF_CONCAT(a, b) a##b
#define CPF_CONCAT(a, b) _CPF_CONCAT(a, b)

//////////////////////////////////////////////////////////////////////////
#define CPF_COUNTOF(a) (sizeof(a) / sizeof(decltype(a)))

/**
 * @brief General assertion.
 * @param exp The expression to assert on.
 */
#define CPF_ASSERT(exp)		{if(!(exp)) CPF_DEBUG_BREAK;}

/**
 * @brief Always assert.
 */
#define CPF_ASSERT_ALWAYS	{CPF_DEBUG_BREAK;}
