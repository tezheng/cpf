//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/BinaryWriter.hpp"

using namespace CPF;
using namespace IO;


//////////////////////////////////////////////////////////////////////////
BinaryWriter::BinaryWriter(Stream* strp)
	: mpStream(strp)
{}

BinaryWriter::~BinaryWriter()
{}

int64_t BinaryWriter::Write(bool& b) const
{
	uint32_t temp = uint32_t(b);
	auto result = mpStream->Write(&temp, sizeof(uint32_t));
	return result.GetOK();
}

int64_t BinaryWriter::Write(String& s) const
{
	// Serialize the size.
	uint32_t size = uint32_t(s.size());
	Write(size);

	// Write the string content.
	for (uint32_t i = 0; i < size; ++i)
		Write(s[i]);

	return size + 4;
}

int64_t BinaryWriter::Write(WString& s) const
{
	// Serialize the size.
	uint32_t size = uint32_t(s.size());
	Write(size);

	// Write the string content.
	for (uint32_t i = 0; i < size; ++i)
		Write(s[i]);

	return size + 4;
}

int64_t BinaryWriter::Write(Std::Utf8String& s) const
{
	uint32_t size = uint32_t(s.data().size());
	Write(size);
	
	for (uint8_t c : s.data())
		Write(c);
	
	return size + 4;
}

int64_t BinaryWriter::Write(char& c) const
{
	return mpStream->Write(&c, sizeof(c)).GetOK();
}

int64_t BinaryWriter::Write(wchar_t& c) const
{
	return mpStream->Write(&c, sizeof(c)).GetOK();
}

int64_t BinaryWriter::Write(int8_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(int16_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(int32_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(int64_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(uint8_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(uint16_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(uint32_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(uint64_t& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(float& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Write(double& v) const
{
	return mpStream->Write(&v, sizeof(v)).GetOK();
}

int64_t BinaryWriter::Align(int a) const
{
	CPF_ASSERT((a & (a - 1)) == 0);
	auto current = mpStream->GetPosition();
	auto offset = (current.GetOK() + (a - 1)) & (a - 1);

	uint8_t v = 0;
	for (auto i = 0; i < offset; ++i)
		mpStream->Write(&v, 1);

	return *this;
}

int64_t BinaryWriter::Pad(int v) const
{
	uint8_t pad = 0;
	for (auto i = 0; i < v; ++i)
		mpStream->Write(&pad, 1);
	return v;
}


BinaryWriter::operator bool() const
{
	return bool(mpStream);
}

Stream* BinaryWriter::GetStream() const
{
	return mpStream;
}
