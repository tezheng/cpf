//////////////////////////////////////////////////////////////////////////
#include "Renderable.hpp"

using namespace CPF;

Renderable::Renderable(Plugin::iRegistry*, GOM::iUnknown*)
{}

GOM::Result CPF_STDCALL Renderable::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;

		case iRenderable::kIID.GetID():
			*outIface = static_cast<iRenderable*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


void CPF_STDCALL Renderable::SetSystem(MultiCore::iSystem*)
{}

MultiCore::iSystem* CPF_STDCALL Renderable::GetSystem()
{
	return nullptr;
}

EntityService::iEntity* CPF_STDCALL Renderable::GetEntity() const
{
	return nullptr;
}

void CPF_STDCALL Renderable::SetEntity(EntityService::iEntity*)
{}

void CPF_STDCALL Renderable::Initialize()
{}

void CPF_STDCALL Renderable::Shutdown()
{}

void CPF_STDCALL Renderable::Activate()
{}

void CPF_STDCALL Renderable::Deactivate()
{}
