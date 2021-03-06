//////////////////////////////////////////////////////////////////////////
#include "IDL/ParseTree/Visitor.hpp"

using namespace IDL;

//////////////////////////////////////////////////////////////////////////
CPF::String TrimStringLit(const CPF::String& lit)
{
	if (lit.empty())
		return CPF::String();
	return CPF::String(lit.begin() + 1, lit.end() - 1);
}

CPF::String TrimCharLit(const CPF::String& lit, bool& isEscape)
{
	isEscape = false;
	CPF::String result = TrimStringLit(lit);
	if (result[0] == '\\')
	{
		isEscape = true;
		return CPF::String(result.begin() + 1, result.end());
	}
	return result;
}

int64_t ParseOctal(const CPF::String& lit)
{
	int64_t result = 0;
	for (const auto c : lit)
	{
		result *= 8;
		result += int64_t(c - '0');
	}
	return result;
}

SymbolPath ParseQualifiedIdent(IDLParser::Qualified_identContext* ctx)
{
	const auto ident = ctx->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_part())
	{
		path.Push(CPF::String(p->IDENT()->toString().c_str()));
	}
	return path;
}

//////////////////////////////////////////////////////////////////////////
Visitor::Visitor()
{}

antlrcpp::Any Visitor::visitMain(IDLParser::MainContext *ctx)
{
	Emit<Start>();
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitModule_stmt(IDLParser::Module_stmtContext *ctx)
{
	const auto ident = ctx->qualified_ident()->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_ident()->qualified_part())
	{
		path.Push(CPF::String(p->IDENT()->toString().c_str()));
	}
	Emit<ModuleStmt>(path);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitSuccess_stmt(IDLParser::Success_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<SuccessType>(name, subSystem, desc);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFailure_stmt(IDLParser::Failure_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<FailureType>(name, subSystem, desc);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *ctx)
{
	String name = ctx->IDENT()->toString();
	Emit<ImportStmt>(name);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx)
{
	String source;
	if (ctx->all_or_ident()->IDENT())
		source = ctx->all_or_ident()->IDENT()->toString();
	else
		source = "*";
	Emit<ImportFromStmt>(source, ParseQualifiedIdent(ctx->qualified_ident()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_decl(IDLParser::Interface_declContext *ctx)
{
	InterfaceDecl decl;
	decl.mName = ctx->IDENT()->toString();
	if (ctx->interface_super())
	{
		// Have a parent.
		decl.mSuper = ParseQualifiedIdent(ctx->interface_super()->qualified_ident());
	}

	for (const auto& item : ctx->interface_block()->interface_item())
	{
		if (item->const_def())
		{
			auto constDef = item->const_def();
			if (constDef->const_class_id_def())
			{
				auto constIDDef = constDef->const_class_id_def();
				ClassID classID;
				classID.mName = constIDDef->IDENT()->toString();
				classID.mValue = TrimStringLit(constIDDef->string_lit()->STRING_LIT()->toString());
				decl.mClassIDs.push_back(classID);
			}
		}
		else if (item->enum_def())
		{

		}
		else if (item->function_decl())
		{
			auto func = item->function_decl();
			FunctionDecl funcDecl;
			funcDecl.mName = func->IDENT()->toString();
			funcDecl.mReturnType = ParseTypeDecl(func->type_decl());
			funcDecl.mConst = (func->Const() != nullptr ? true : false);
			if (func->function_param_list())
			{
				for (auto param : func->function_param_list()->function_param())
				{
					ParamDecl paramDecl;
					paramDecl.mName = param->IDENT() ? param->IDENT()->toString() : String();
					paramDecl.mDir = ParseParamDir(param->param_dir_qualifier());
					paramDecl.mType = ParseTypeDecl(param->type_decl());
					funcDecl.mParams.push_back(paramDecl);
				}
			}

			decl.mFunctions.push_back(funcDecl);
		}
		else if (item->callback_decl())
		{
			auto eventCtx = item->callback_decl();
			CallbackDecl callbackDecl;
			callbackDecl.mName = eventCtx->IDENT()->toString();
			callbackDecl.mReturnType = ParseTypeDecl(eventCtx->type_decl());
			if (eventCtx->function_param_list())
			{
				for (auto param : eventCtx->function_param_list()->function_param())
				{
					ParamDecl paramDecl;
					paramDecl.mName = param->IDENT() ? param->IDENT()->toString() : String();
					paramDecl.mType = ParseTypeDecl(param->type_decl());
					callbackDecl.mParams.push_back(paramDecl);
				}
			}
			decl.mCallbacks.push_back(callbackDecl);
		}
	}

	Emit<InterfaceDeclStmt>(decl);
	return defaultResult();
}

antlrcpp::Any Visitor::visitInterface_fwd(IDLParser::Interface_fwdContext *ctx)
{
	Emit<InterfaceFwdStmt>(ParseQualifiedIdent(ctx->qualified_ident()).ToString("::"));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitCallback_decl(IDLParser::Callback_declContext *ctx)
{
	CallbackDecl callbackDecl;
	callbackDecl.mName = ctx->IDENT()->toString();
	callbackDecl.mReturnType = ParseTypeDecl(ctx->type_decl());
	if (ctx->function_param_list())
	{
		for (auto param : ctx->function_param_list()->function_param())
		{
			ParamDecl paramDecl;
			paramDecl.mName = param->IDENT() ? param->IDENT()->toString() : String();
			paramDecl.mType = ParseTypeDecl(param->type_decl());
			callbackDecl.mParams.push_back(paramDecl);
		}
	}
	Emit<CallbackDeclStmt>(callbackDecl);
	return defaultResult();
}

antlrcpp::Any Visitor::visitStruct_fwd(IDLParser::Struct_fwdContext *ctx)
{
	Emit<StructFwdStmt>(ParseQualifiedIdent(ctx->qualified_ident()).ToString("::"));
	return visitChildren(ctx);
}

Visitor::MemberInitValue Visitor::ParseInitValue(IDLParser::Member_init_valueContext* ctx)
{
	Visitor::MemberInitValue value;
	value.mAsType = Visitor::Type::None;
	if (ctx->qualified_ident())
	{
		value.mType = ctx->DEFAULT() ?
			MemberInitValue::Default :
			MemberInitValue::Identifier;
		value.mIdent = ParseQualifiedIdent(ctx->qualified_ident()).ToString("::");
	}
	else if (ctx->integer_lit())
	{
		value.mType = MemberInitValue::Integer;
		value.mInt = ParseIntegerLit(ctx->integer_lit());
	}
	else if (ctx->float_lit())
	{
		value.mType = MemberInitValue::Float;
		sscanf(ctx->float_lit()->toString().c_str(), "%f", &value.mFloat);
	}
	else if (ctx->string_lit())
	{
		value.mType = MemberInitValue::Str;
		value.mString = ctx->string_lit()->STRING_LIT()->toString();
	}
	if (ctx->init_as_type())
	{
		auto as_type = ctx->init_as_type();
		if (as_type->integral_type())
		{
			value.mAsType = ParseIntegralType(as_type->integral_type());
		}
		else if (as_type->float_type())
		{
			CPF_ASSERT_ALWAYS; // TODO.
		}
	}
	return value;
}

antlrcpp::Any Visitor::visitStruct_decl(IDLParser::Struct_declContext *ctx)
{
	UnionOrStructDecl structDecl;
	structDecl.mUnion = false;
	structDecl.mName = ctx->IDENT()->toString();
	{
		auto members = ctx->struct_block()->struct_item();
		for (const auto& item : members)
		{
			if (item->const_def())
			{

			}
			else if (item->enum_def())
			{

			}
			else if (item->member_decl())
			{
				auto decl = item->member_decl();
				DataMemberDecl data;
				data.mName = decl->IDENT()->toString();
				data.mType = ParseTypeDecl(decl->type_decl());
				data.mArrayDimensions.mType = MemberInitValue::None;
				if (decl->integer_lit())
				{
					data.mArrayDimensions.mType = MemberInitValue::Integer;
					data.mArrayDimensions.mInt = int32_t(ParseIntegerLit(decl->integer_lit()));
				}
				else if (decl->qualified_ident())
				{
					data.mArrayDimensions.mType = MemberInitValue::Identifier;
					data.mArrayDimensions.mIdent = ParseQualifiedIdent(decl->qualified_ident()).ToString("::");
				}

				if (decl->member_init() != nullptr)
				{
					for (auto& initCtx : decl->member_init()->member_init_value())
					{
						data.mInitializers.push_back(ParseInitValue(initCtx));
					}
				}

				structDecl.mDataMembers[int(OsType::eNone)].push_back(data);
			}
		}
	}
	auto os_members = ctx->struct_block()->os_specific();
	for (const auto& item : os_members)
	{
		int index = int(OsType::eNone);
		if (item->os_tag()->Windows())
			index = int(OsType::eWindows);
		else if (item->os_tag()->Darwin())
			index = int(OsType::eDarwin);

		auto members = item->struct_item();
		for (const auto& it : members)
		{
			if (it->const_def())
			{

			}
			else if (it->enum_def())
			{

			}
			else if (it->member_decl())
			{
				auto decl = it->member_decl();
				DataMemberDecl data;
				data.mName = decl->IDENT()->toString();
				data.mType = ParseTypeDecl(decl->type_decl());
				data.mArrayDimensions.mType = MemberInitValue::None;
				if (decl->integer_lit())
				{
					data.mArrayDimensions.mType = MemberInitValue::Integer;
					data.mArrayDimensions.mInt = int32_t(ParseIntegerLit(decl->integer_lit()));
				}
				else if (decl->qualified_ident())
				{
					data.mArrayDimensions.mType = MemberInitValue::Identifier;
					data.mArrayDimensions.mIdent = ParseQualifiedIdent(decl->qualified_ident()).ToString("::");
				}
				structDecl.mDataMembers[index].push_back(data);
			}
		}
	}

	Emit<StructDeclStmt>(structDecl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitUnion_fwd(IDLParser::Union_fwdContext *ctx)
{
	Emit<UnionFwdStmt>(ParseQualifiedIdent(ctx->qualified_ident()).ToString("::"));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitUnion_decl(IDLParser::Union_declContext *ctx)
{
	UnionOrStructDecl structDecl;
	structDecl.mUnion = true;
	structDecl.mName = ctx->IDENT()->toString();
	auto members = ctx->struct_block()->struct_item();
	for (const auto& item : members)
	{
		if (item->const_def())
		{

		}
		else if (item->enum_def())
		{

		}
		else if (item->member_decl())
		{
			auto decl = item->member_decl();
			DataMemberDecl data;
			data.mName = decl->IDENT()->toString();
			data.mType = ParseTypeDecl(decl->type_decl());
			data.mArrayDimensions.mType = MemberInitValue::None;
			if (decl->integer_lit())
			{
				data.mArrayDimensions.mType = MemberInitValue::Integer;
				data.mArrayDimensions.mInt = int32_t(ParseIntegerLit(decl->integer_lit()));
			}
			else if (decl->qualified_ident())
			{
				data.mArrayDimensions.mType = MemberInitValue::Identifier;
				data.mArrayDimensions.mIdent = ParseQualifiedIdent(decl->qualified_ident()).ToString("::");
			}
			structDecl.mDataMembers[int(OsType::eNone)].push_back(data);
		}
	}

	Emit<UnionDeclStmt>(structDecl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitEnum_fwd(IDLParser::Enum_fwdContext *ctx)
{
	Emit<EnumForwardStmt>(ctx->IDENT()->toString(), ParseIntegralType(ctx->enum_type()->integral_type()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitEnum_def(IDLParser::Enum_defContext *ctx)
{
	EnumDecl enumDecl;
	enumDecl.mName = ctx->IDENT()->toString();
	enumDecl.mType = Visitor::Type::Void;
	if (ctx->enum_type() && ctx->enum_type()->integral_type())
		enumDecl.mType = ParseIntegralType(ctx->enum_type()->integral_type());

	auto items = ctx->enum_elements()->enum_item();
	for (const auto& item : items)
	{
		EnumEntry entry;
		entry.mName = item->IDENT()->toString();
		if (item->EQUALS())
		{
			entry.mValue = ParseEnumExpr(item->enum_expr());
		}
		enumDecl.mEntries.push_back(entry);
	}

	Emit<EnumDeclStmt>(enumDecl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFlags_fwd(IDLParser::Flags_fwdContext *ctx)
{
	Emit<FlagsForwardStmt>(ctx->IDENT()->toString(), ParseIntegralType(ctx->enum_type()->integral_type()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFlags_def(IDLParser::Flags_defContext *ctx)
{
	EnumDecl enumDecl;
	enumDecl.mName = ctx->IDENT()->toString();
	enumDecl.mType = Visitor::Type::Void;
	if (ctx->enum_type() && ctx->enum_type()->integral_type())
		enumDecl.mType = ParseIntegralType(ctx->enum_type()->integral_type());

	auto items = ctx->enum_elements()->enum_item();
	for (const auto& item : items)
	{
		EnumEntry entry;
		entry.mName = item->IDENT()->toString();
		if (item->EQUALS())
		{
			entry.mValue = ParseEnumExpr(item->enum_expr());
		}
		enumDecl.mEntries.push_back(entry);
	}

	Emit<FlagsDeclStmt>(enumDecl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitConst_integral_def(IDLParser::Const_integral_defContext *ctx)
{
	ConstIntegral value;
	value.mName = ctx->IDENT()->toString();
	value.mType = ParseIntegralType(ctx->integral_type());
	value.mValue = ParseIntegerLit(ctx->integer_lit());
	Emit<ConstIntegralStmt>(value);
	return visitChildren(ctx);
}

Visitor::Type Visitor::ParseIntegralType(IDLParser::Integral_typeContext* integralType)
{
	Type result;

	if (integralType->U8()) result = Type::U8;
	else if (integralType->S8()) result = Type::S8;
	else if (integralType->U16()) result = Type::U16;
	else if (integralType->S16()) result = Type::S16;
	else if (integralType->U32()) result = Type::U32;
	else if (integralType->S32()) result = Type::S32;
	else if (integralType->U64()) result = Type::U64;
	else if (integralType->S64()) result = Type::S64;
	else { result = Type::Void; CPF_ASSERT_ALWAYS }

	return result;
}

Visitor::ParamDir Visitor::ParseParamDir(IDLParser::Param_dir_qualifierContext* ctx)
{
	ParamDir dir{};

	if(ctx)
	{
		if(ctx->In())
		{
			dir.mIn = true;
		}
		if(ctx->Out())
		{
			dir.mOut = true;
		}
	}

	return dir;
}

Visitor::TypeDecl Visitor::ParseTypeDecl(IDLParser::Type_declContext* typeDecl)
{
	TypeDecl result;
	result.mConst = typeDecl->type_modifier() == nullptr ? false : true;

	auto anyType = typeDecl->any_type();
	if (anyType->integral_type())
	{
		result.mType = ParseIntegralType(anyType->integral_type());
	}
	else if (anyType->float_type())
	{
		auto floatType = anyType->float_type();
		if (floatType->F32()) result.mType = Type::F32;
		else if (floatType->F64()) result.mType = Type::F64;
	}
	else if (anyType->utility_type())
	{
		auto utilType = anyType->utility_type();
		if (utilType->Void()) result.mType = Type::Void;
		else if (utilType->RESULT()) result.mType = Type::Result;
	}
	else if (anyType->qualified_ident())
	{
		result.mType = Type::Ident;
		result.mIdent = ParseQualifiedIdent(anyType->qualified_ident());
	}
	else
	{
		// Error.
	}

	if (typeDecl->pointer_type())
	{
		for (const auto& ptr : typeDecl->pointer_type()->pointer_decl())
		{
			Pointer pointer;
			if (ptr->Const())
				pointer.mConst = true;
			else
				pointer.mConst = false;
			result.mPointer.push_back(pointer);
		}
	}

	return result;
}

CPF::String Visitor::ParseExprValue(IDLParser::Expr_valueContext* expr)
{
	if (expr->qualified_ident())
	{
		return ParseQualifiedIdent(expr->qualified_ident()).ToString("::");
	}
	else if (expr->integer_lit())
	{
		auto litExpr = expr->integer_lit();
		return std::to_string(ParseIntegerLit(litExpr));
	}
	else if (expr->enum_expr())
	{
		return ParseExprAddSub(expr->enum_expr()->expr_add_sub());
	}

	// Shouldn't be able to get here.
	CPF_ASSERT_ALWAYS;
	return "";
}

CPF::String Visitor::ParseExprLogical(IDLParser::Expr_logicalContext* expr)
{
	if (expr->PIPE())
	{
		auto lhs = ParseExprLogical(expr->expr_logical());
		auto rhs = ParseExprValue(expr->expr_value());
		return std::to_string(atoi(lhs.c_str()) | atoi(rhs.c_str()));
	}
	else if (expr->expr_value())
		return ParseExprValue(expr->expr_value());

	// Shouldn't be able to get here.
	CPF_ASSERT_ALWAYS;
	return "";
}

CPF::String Visitor::ParseExprShift(IDLParser::Expr_shiftContext* expr)
{
	if (expr->LSHIFT())
	{
		auto lhs = ParseExprShift(expr->expr_shift());
		auto rhs = ParseExprLogical(expr->expr_logical());
		return std::to_string(atoi(lhs.c_str()) << atoi(rhs.c_str()));
	}
	else if (expr->RSHIFT())
	{
		auto lhs = ParseExprShift(expr->expr_shift());
		auto rhs = ParseExprLogical(expr->expr_logical());
		return std::to_string(atoi(lhs.c_str()) >> atoi(rhs.c_str()));
	}
	else if (expr->expr_logical())
		return ParseExprLogical(expr->expr_logical());

	// Shouldn't be able to get here.
	CPF_ASSERT_ALWAYS;
	return "";
}

CPF::String Visitor::ParseExprMulDiv(IDLParser::Expr_mul_divContext* expr)
{
	if (expr->STAR())
	{
		auto lhs = ParseExprMulDiv(expr->expr_mul_div());
		auto rhs = ParseExprShift(expr->expr_shift());
		return std::to_string(atoi(lhs.c_str()) * atoi(rhs.c_str()));
	}
	else if (expr->SLASH())
	{
		auto lhs = ParseExprMulDiv(expr->expr_mul_div());
		auto rhs = ParseExprShift(expr->expr_shift());
		return std::to_string(atoi(lhs.c_str()) / atoi(rhs.c_str()));
	}
	else if (expr->expr_shift())
		return ParseExprShift(expr->expr_shift());

	// Shouldn't be able to get here.
	CPF_ASSERT_ALWAYS;
	return "";
}

CPF::String Visitor::ParseExprAddSub(IDLParser::Expr_add_subContext* expr)
{
	if (expr->PLUS())
	{
		auto lhs = ParseExprAddSub(expr->expr_add_sub());
		auto rhs = ParseExprMulDiv(expr->expr_mul_div());
		return std::to_string(atoi(lhs.c_str()) + atoi(rhs.c_str()));
	}
	else if (expr->MINUS())
	{
		auto lhs = ParseExprAddSub(expr->expr_add_sub());
		auto rhs = ParseExprMulDiv(expr->expr_mul_div());
		return std::to_string(atoi(lhs.c_str()) - atoi(rhs.c_str()));
	}
	else if (expr->expr_mul_div())
		return ParseExprMulDiv(expr->expr_mul_div());

	// Shouldn't be able to get here.
	CPF_ASSERT_ALWAYS;
	return "";
}


CPF::String Visitor::ParseEnumExpr(IDLParser::Enum_exprContext* expr)
{
	auto addSubExpr = expr->expr_add_sub();
	if (addSubExpr->expr_mul_div())
		return ParseExprAddSub(addSubExpr);
	return 0;
}

int64_t Visitor::ParseIntegerLit(IDLParser::Integer_litContext* lit)
{
	if (lit)
	{
		if (lit->BIN_LIT())
		{

		}
		else if (lit->DECIMAL_LIT())
		{
			return atoi(lit->DECIMAL_LIT()->toString().c_str());
		}
		else if (lit->HEX_LIT())
		{
			int32_t hexLit;
			::sscanf(lit->HEX_LIT()->toString().c_str(), "%x", &hexLit);
			return hexLit;
		}
		else if (lit->OCT_LIT())
		{

		}
		else if (lit->char_lit())
		{
			bool isEscape = false;
			String charString = TrimCharLit(lit->char_lit()->CHAR_LIT()->toString(), isEscape);
			if (isEscape)
			{
				switch (charString[0])
				{
				case 'a': return 0x07;
				case 'b': return 0x08;
				case 'f': return 0x0c;
				case 'n': return 0x0a;
				case 'r': return 0x0d;
				case 't': return 0x09;
				case 'v': return 0x0b;
				case '\\': return 0x5c;
				case '\'': return 0x27;
				case '\"': return 0x22;
				case '\?': return 0x3f;
				// TODO: handle hex.
				}
				return ParseOctal(charString);
			}
			return int64_t(charString[0]);
		}
	}
	return 0x7fffffff;
}
