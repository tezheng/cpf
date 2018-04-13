#include "CPF/IO/Globbing.hpp"
#include "CPF/Std/Utf8String.hpp"

using namespace CPF;
using namespace IO;

CPF_EXPORT bool IO::Glob(const STD::Utf8String& pattern, const STD::Utf8String& value)
{
	if (pattern.empty() || value.empty())
		return false;

	STD::Utf8String::const_iterator inString = value.begin();
	STD::Utf8String::const_iterator inPattern = pattern.begin();
	STD::Utf8String::const_iterator current = value.end();

	while ((inString!=value.end()) && (inPattern == pattern.end() || *inPattern != uint32_t('*')))
	{
		if ((*inPattern != *inString) && (*inPattern != uint32_t('?')))
			return false;
		++inPattern;
		++inString;
	}

	STD::Utf8String::const_iterator mp;
	while (inString != value.end())
	{
		if (inPattern != pattern.end() && *inPattern == uint32_t('*'))
		{
			if (++inPattern == pattern.end())
				return true;
			mp = inPattern;
			current = inString + 1;
		}
		else if (
			(inPattern != pattern.end()) &&
			((*inPattern == *inString) || (*inPattern == uint32_t('?'))))
		{
			++inPattern;
			++inString;
		}
		else
		{
			inPattern = mp;
			if (current == value.end())
				return false;
			inString = current++;
		}
	}

	while (inPattern != pattern.end() && *inPattern == uint32_t('*'))
		++inPattern;
	return inPattern == pattern.end();
}
