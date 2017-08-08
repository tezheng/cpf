//////////////////////////////////////////////////////////////////////////
#include "AST/Namespace.hpp"

using namespace AST;

SymbolType Namespace::GetType() const
{
	return SymbolType::eNamespace;
}

Namespace::Namespace(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
{
}

Namespace::~Namespace()
{}


//////////////////////////////////////////////////////////////////////////
SymbolType EndNamespace::GetType() const
{
	return SymbolType::eEndNamespace;
}

EndNamespace::EndNamespace(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
{
}

EndNamespace::~EndNamespace()
{}
