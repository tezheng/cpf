//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CppGenerator.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"
#include "IO/Path.hpp"
#include "GOM/Types.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace CPF::Placeholders;

//////////////////////////////////////////////////////////////////////////
void CppGenerator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(CPF::Bind(&CppGenerator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(CPF::Bind(&CppGenerator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(CPF::Bind(&CppGenerator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(CPF::Bind(&CppGenerator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportStmt>(CPF::Bind(&CppGenerator::OnImportStmt, this, _1));
	visitor.On<Visitor::ImportFromStmt>(CPF::Bind(&CppGenerator::OnImportFromStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::Bind(&CppGenerator::OnInterfaceDeclStmt, this, _1));
	visitor.On<Visitor::InterfaceFwdStmt>(CPF::Bind(&CppGenerator::OnInterfaceFwdStmt, this, _1));
	visitor.On<Visitor::StructFwdStmt>(CPF::Bind(&CppGenerator::OnStructFwdStmt, this, _1));
	visitor.On<Visitor::StructDeclStmt>(CPF::Bind(&CppGenerator::OnStructStmt, this, _1));
	visitor.On<Visitor::EnumForwardStmt>(CPF::Bind(&CppGenerator::OnEnumForwardStmt, this, _1, _2));
	visitor.On<Visitor::EnumDeclStmt>(CPF::Bind(&CppGenerator::OnEnumDeclStmt, this, _1));
	visitor.On<Visitor::UnionFwdStmt>(CPF::Bind(&CppGenerator::OnUnionFwdStmt, this, _1));
	visitor.On<Visitor::UnionDeclStmt>(CPF::Bind(&CppGenerator::OnStructStmt, this, _1));
	visitor.On<Visitor::ConstIntegralStmt>(CPF::Bind(&CppGenerator::OnConstIntegral, this, _1));
	visitor.On<Visitor::FlagsForwardStmt>(CPF::Bind(&CppGenerator::OnFlagsForwardStmt, this, _1, _2));
	visitor.On<Visitor::FlagsDeclStmt>(CPF::Bind(&CppGenerator::OnFlagsDeclStmt, this, _1));
}

void CppGenerator::End()
{
	for (const auto& part : mModule.GetPath())
	{
		(void)part;
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

//

void CppGenerator::OnStart()
{
	mpWriter->SetSection(eHeader);
	mpWriter->OutputLine("//////////////////////////////////////////////////////////////////////////");
	mpWriter->OutputLine("#pragma once");
}

void CppGenerator::OnModule(const SymbolPath& path)
{
	mpWriter->LineFeed(eNamespace, eNamespace, CodeWriter::kAnySection);
	mModule = path;
	for (const auto& part : path.GetPath())
	{
		mpWriter->OutputLine("namespace %s", part.c_str());
		mpWriter->OutputLine("{");
		mpWriter->Indent();
	}
}

void CppGenerator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		CPF::GOM::CreateResult(
			0,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CppGenerator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		CPF::GOM::CreateResult(
			1,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CppGenerator::OnImportStmt(const String& name)
{
	mpWriter->LineFeed(eImports, eImports | eHeader, CodeWriter::kAnySection);
	auto path = name + ".hpp";
	mpWriter->OutputLine("#include \"%s\"", path.c_str());
}

void CppGenerator::OnImportFromStmt(const String& item, const SymbolPath& from)
{
	mpWriter->LineFeed(eImports, eImports | eHeader, CodeWriter::kAnySection);
	auto path = CPF::IO::Path::Combine(from.ToString("/"), item + ".hpp");
	mpWriter->OutputLine("#include \"%s\"", path.c_str());
}

void CppGenerator::OnInterfaceDeclStmt(const Visitor::InterfaceDecl& decl)
{
	mpWriter->LineFeed(eInterfaces, eNamespace, CodeWriter::kAnySection);
	if (decl.mSuper.Empty())
		mpWriter->OutputLine("struct %s", decl.mName.c_str());
	else
		mpWriter->OutputLine("struct %s : %s", decl.mName.c_str(), decl.mSuper.ToString("::").c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	//
	mpWriter->SetSection(eConstants);
	CPF::String hashName = (mModule.ToString("::") + "::" + decl.mName).c_str();
	CPF::GOM::InterfaceID iid = CPF::GOM::InterfaceID(CPF::Hash::Crc64(hashName.c_str(), hashName.length()));
	mpWriter->OutputLine("static constexpr GOM::InterfaceID kIID = GOM::InterfaceID(0x%" PRIx64 " /* %s */);",
		iid.GetID(), hashName.c_str());

	// TODO: Extend this to handle the full range of constant types.
	for (const auto& constItem : decl.mClassIDs)
	{
		mpWriter->OutputLine("static constexpr GOM::InstanceID %s = GOM::InstanceID(0x%" PRIx64 " /* %s */);",
			constItem.mName.c_str(),
			CPF::Hash::Crc64(constItem.mValue.c_str(), constItem.mValue.length()),
			constItem.mValue.c_str()
		);
	}

	if (!decl.mCallbacks.empty())
	{
		mpWriter->LineFeed(eEvents, eEvents);
		for (const auto& callbackItem : decl.mCallbacks)
		{
			mpWriter->Output("%susing %s = %s (*) (",
				mpWriter->GetIndentString().c_str(),
				callbackItem.mName.c_str(),
				TypeToString(callbackItem.mReturnType).c_str());

			if (!callbackItem.mParams.empty())
			{
				mpWriter->Output("%s", TypeToString(callbackItem.mParams[0].mType).c_str());
				if (!callbackItem.mParams[0].mName.empty())
					mpWriter->Output(" %s", callbackItem.mParams[0].mName.c_str());

				for (auto it = callbackItem.mParams.begin() + 1; it != callbackItem.mParams.end(); ++it)
				{
					mpWriter->Output(", %s", TypeToString(it->mType).c_str());
					if (!it->mName.empty())
						mpWriter->Output(" %s", it->mName.c_str());
				}
			}
			mpWriter->Output(");");
			mpWriter->LineFeed(eEvents, CodeWriter::kNoSection);
		}
	}

	for (const auto& func : decl.mFunctions)
	{
		mpWriter->LineFeed(eInterfaces, eNamespace, CodeWriter::kAnySection);

		mpWriter->Output("%svirtual %s CPF_STDCALL %s (",
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType).c_str(),
			func.mName.c_str());

		// Parameters.
		if (!func.mParams.empty())
		{
			mpWriter->Output("%s", TypeToString(func.mParams[0].mType).c_str());
			if (!func.mParams[0].mName.empty())
				mpWriter->Output(" %s", func.mParams[0].mName.c_str());

			for (auto it = func.mParams.begin() + 1; it != func.mParams.end(); ++it)
			{
				mpWriter->Output(", %s", TypeToString(it->mType).c_str());
				if (!it->mName.empty())
					mpWriter->Output(" %s", it->mName.c_str());
			}
		}

		if (func.mConst)
			mpWriter->Output(") const = 0;");
		else
			mpWriter->Output(") = 0;");
	}

	if (!decl.mFunctions.empty())
		mpWriter->LineFeed(CodeWriter::kNoSection, CodeWriter::kNoSection, CodeWriter::kAnySection);

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}
#if 0
void CppGenerator::OnClassIDStmt(const Visitor::ClassID& classID)
{
	mpWriter->LineFeed(eConstants, eNamespace, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr GOM::InstanceID %s = GOM::InstanceID(0x%" PRIx64 " /* %s */);",
		classID.mName.c_str(),
		CPF::Hash::Crc64(classID.mValue.c_str(), classID.mValue.length()),
		classID.mValue.c_str()
	);
}
#endif


void CppGenerator::OnInterfaceFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("struct %s;", name.c_str());
}

void CppGenerator::OnStructFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("struct %s;", name.c_str());
}

void CppGenerator::OnUnionFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("union %s;", name.c_str());
}

void CppGenerator::OnStructStmt(const Visitor::UnionOrStructDecl& decl)
{
	bool hasInitializers = false;
	mpWriter->LineFeed(eStructures, eNamespace, CodeWriter::kAnySection);
	if (decl.mUnion)
		mpWriter->OutputLine("union %s", decl.mName.c_str());
	else
		mpWriter->OutputLine("struct %s", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eNone)])
	{
		CPF::String arrayDims = "";
		switch (member.mArrayDimensions.mType)
		{
		case Visitor::MemberInitValue::Integer:
			arrayDims = String("[") + std::to_string(member.mArrayDimensions.mInt) + String("]");
			break;
		case Visitor::MemberInitValue::Identifier:
			arrayDims = String("[k") + member.mArrayDimensions.mIdent + String("]");
			break;
		}

		mpWriter->OutputLine("%s %s%s;",
			TypeToString(member.mType).c_str(),
			member.mName.c_str(),
			arrayDims.c_str());
		if (!member.mInitializers.empty())
			hasInitializers = true;
	}
	if (!decl.mDataMembers[int(Visitor::OsType::eWindows)].empty())
	{
		mpWriter->OutputLineNoIndent("#if CPF_TARGET_WINDOWS");
		for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eWindows)])
		{
			CPF::String arrayDims = "";
			switch (member.mArrayDimensions.mType)
			{
			case Visitor::MemberInitValue::Integer:
				arrayDims = String("[") + std::to_string(member.mArrayDimensions.mInt) + String("]");
				break;
			case Visitor::MemberInitValue::Identifier:
				arrayDims = String("[k") + member.mArrayDimensions.mIdent + String("]");
				break;
			}
			mpWriter->OutputLine("%s %s%s;",
				TypeToString(member.mType).c_str(),
				member.mName.c_str(),
				arrayDims.c_str());
			if (!member.mInitializers.empty())
				hasInitializers = true;
		}
		mpWriter->OutputLineNoIndent("#endif");
	}
	if (!decl.mDataMembers[int(Visitor::OsType::eDarwin)].empty())
	{
		mpWriter->OutputLineNoIndent("#if CPF_TARGET_DARWIN");
		for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eDarwin)])
		{
			CPF::String arrayDims = "";
			switch (member.mArrayDimensions.mType)
			{
			case Visitor::MemberInitValue::Integer:
				arrayDims = String("[") + std::to_string(member.mArrayDimensions.mInt) + String("]");
				break;
			case Visitor::MemberInitValue::Identifier:
				arrayDims = String("[k") + member.mArrayDimensions.mIdent + String("]");
				break;
			}
			mpWriter->OutputLine("%s %s%s;",
				TypeToString(member.mType).c_str(),
				member.mName.c_str(),
				arrayDims.c_str());
			if (!member.mInitializers.empty())
				hasInitializers = true;
		}
		mpWriter->OutputLineNoIndent("#endif");
	}
	mpWriter->Unindent();
	mpWriter->OutputLine("};");

	// TODO: Does not handle items with os specifics correctly. (As in not at all!)
	if (hasInitializers)
	{
		mpWriter->LineFeed(eStructures, 0, -1);
		mpWriter->OutputLine("template <> inline %s Defaults() {", decl.mName.c_str());
		mpWriter->Indent();
		mpWriter->OutputLine("return %s{", decl.mName.c_str());
		mpWriter->Indent();

		for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eNone)])
		{
			bool isLastMember = &member == &decl.mDataMembers[int(Visitor::OsType::eNone)].back();
			const auto& initializers = member.mInitializers;
			if (initializers.size() == 1)
			{
				switch (initializers[0].mType)
				{
				case Visitor::MemberInitValue::Integer:
					if (initializers[0].mAsType != Visitor::Type::None)
					{
						auto type = TypeToString(initializers[0].mAsType);
						mpWriter->OutputLine("%s(%d)%s", type.c_str(), int(initializers[0].mInt), isLastMember ? "" : ",");
					}
					else
						mpWriter->OutputLine("%d%s", int(initializers[0].mInt), isLastMember ? "" : ",");
					break;
				case Visitor::MemberInitValue::Identifier:
					mpWriter->OutputLine("%s%s", initializers[0].mIdent.c_str(), isLastMember ? "" : ",");
					break;
				case Visitor::MemberInitValue::Float:
					mpWriter->OutputLine("%f%s", initializers[0].mFloat, isLastMember ? "" : ",");
					break;
				case Visitor::MemberInitValue::Default:
					mpWriter->OutputLine("Defaults<%s>()%s", initializers[0].mIdent.c_str(), isLastMember ? "" : ",");
					break;
				case Visitor::MemberInitValue::Str:
					mpWriter->OutputLine("%s%s", initializers[0].mString.c_str(), isLastMember ? "" : ",");
					break;
				}
			}
			else
			{
				mpWriter->OutputLine("{", decl.mName.c_str());
				mpWriter->Indent();

				for (const auto& initValue : initializers)
				{
					bool lastValue = &initValue == &initializers.back();
					switch (initValue.mType)
					{
					case Visitor::MemberInitValue::Integer:
						if (initValue.mAsType != Visitor::Type::None)
						{
							auto type = TypeToString(initValue.mAsType);
							mpWriter->OutputLine("%s(%d)%s", type.c_str(), int(initValue.mInt), isLastMember ? "" : ",");
						}
						else
							mpWriter->OutputLine("%d%s", int(initValue.mInt), lastValue ? "" : ",");
						break;
					case Visitor::MemberInitValue::Identifier:
						mpWriter->OutputLine("%s%s", initValue.mIdent.c_str(), lastValue ? "" : ",");
						break;
					case Visitor::MemberInitValue::Float:
						mpWriter->OutputLine("%f%s", initValue.mFloat, lastValue ? "" : ",");
						break;
					case Visitor::MemberInitValue::Default:
						mpWriter->OutputLine("Defaults<%s>()%s", initValue.mIdent.c_str(), lastValue ? "" : ",");
						break;
					case Visitor::MemberInitValue::Str:
						mpWriter->OutputLine("%s%s", initValue.mString.c_str(), lastValue ? "" : ",");
						break;
					}
				}

				mpWriter->Unindent();
				mpWriter->OutputLine("}%s", isLastMember ? "" : ",");
			}
		}

		mpWriter->Unindent();
		mpWriter->OutputLine("};");
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

void CppGenerator::OnEnumForwardStmt(const String& name, Visitor::Type type)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	if (type == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", name.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s;", name.c_str(), TypeToString(type).c_str());
}

void CppGenerator::OnEnumDeclStmt(const Visitor::EnumDecl& decl)
{
	mpWriter->LineFeed(eStructures, eNamespace, CodeWriter::kAnySection);
	if (decl.mType == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", decl.mName.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s", decl.mName.c_str(), TypeToString(decl.mType).c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& item : decl.mEntries)
	{
		if (!item.mValue.empty())
			mpWriter->OutputLine("%s = %s,", item.mName.c_str(), item.mValue.c_str());
		else
			mpWriter->OutputLine("%s,", item.mName.c_str());
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

void CppGenerator::OnFlagsForwardStmt(const String& name, Visitor::Type type)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	if (type == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", name.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s;", name.c_str(), TypeToString(type).c_str());
}

void CppGenerator::OnFlagsDeclStmt(const Visitor::EnumDecl& decl)
{
	mpWriter->LineFeed(eStructures, eNamespace, CodeWriter::kAnySection);
	if (decl.mType == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", decl.mName.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s", decl.mName.c_str(), TypeToString(decl.mType).c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& item : decl.mEntries)
	{
		if (!item.mValue.empty())
			mpWriter->OutputLine("%s = %s,", item.mName.c_str(), item.mValue.c_str());
		else
			mpWriter->OutputLine("%s,", item.mName.c_str());
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
	mpWriter->OutputLine("CPF_ENUM_FLAG_TYPE(%s);", decl.mName.c_str());
}

void CppGenerator::OnConstIntegral(const Visitor::ConstIntegral& constIntegral)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr %s k%s = %d;",
		TypeToString(constIntegral.mType).c_str(),
		constIntegral.mName.c_str(),
		constIntegral.mValue);
}

CPF::String CppGenerator::TypeToString(const Visitor::Type type)
{
	switch (type)
	{
	case Visitor::Type::U8: return "uint8_t";
	case Visitor::Type::S8: return "int8_t";
	case Visitor::Type::U16: return "uint16_t";
	case Visitor::Type::S16: return "int16_t";
	case Visitor::Type::U32: return "uint32_t";
	case Visitor::Type::S32: return "int32_t";
	case Visitor::Type::U64: return "uint64_t";
	case Visitor::Type::S64: return "int64_t";

	case Visitor::Type::F32: return "float";
	case Visitor::Type::F64: return "double";

	case Visitor::Type::Void: return "void";
	case Visitor::Type::Result: return "GOM::Result";
	}
	return "";
}

CPF::String CppGenerator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	if (decl.mConst)
		result += "const ";
	switch (decl.mType)
	{
	case Visitor::Type::Ident:
		result += decl.mIdent.ToString("::");
		break;
	default:
		result += TypeToString(decl.mType);
		break;
	}
	for (const auto& ptr : decl.mPointer)
	{
		if (ptr.mConst)
			result += " const *";
		else
			result += "*";
	}
	return result;
}
