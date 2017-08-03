//////////////////////////////////////////////////////////////////////////
#include "IO/TextReader.hpp"

using namespace Cpf;
using namespace IO;


//////////////////////////////////////////////////////////////////////////
TextReader::TextReader(Stream* strp)
	: mpStream(strp)
{
	mpStream->AddRef();
}

TextReader::~TextReader()
{}

TextReader::operator bool() const
{
	return bool(mpStream);
}

Stream* TextReader::GetStream() const
{
	return mpStream;
}

int64_t TextReader::ReadLine(String& out)
{
	int64_t result = 0;
	uint8_t current;
	out.clear();
	while (mpStream->Read(&current, sizeof(current)))
	{
		if (current == 0x0d || current == 0x0a)
		{
			if (current == 0x0d)
				continue;  // Skip it.
			break;
		}
		else
		{
			++result;
			out += current;
		}
	}
	return result;
}

int64_t TextReader::ReadAll(String& out)
{
	int64_t result = 0;
	out.clear();
	uint8_t current;
	while (mpStream->Read(&current, sizeof(current)))
	{
		++result;
		out += current;
	}
	return result;
}
