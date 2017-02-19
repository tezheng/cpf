//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Stage.hpp"
#include "MultiCore/Service.hpp"
#include "MultiCore/Distributor.hpp"

using namespace Cpf;
using namespace MultiCore;

Stage::Stage(Service* service, StageID id, const Dependencies& dependencies)
	: mpService(service)
	, mID(id)
	, mDependencies(dependencies)
{
	
}

Stage::~Stage()
{}

Service* Stage::GetService() const
{
	return mpService;
}

StageID Stage::GetID() const
{
	return mID;
}

bool Stage::operator == (const Stage& rhs) const
{
	return (mpService == rhs.mpService && mID == rhs.mID);
}

bool Stage::operator != (const Stage& rhs) const
{
	return (mpService != rhs.mpService || mID != rhs.mID);
}

bool Stage::operator > (const Stage& rhs) const
{
	// This stage is 'greater' than the rhs if this has a dependency on rhs.
	for (int i=0; i<mDependencies.size(); ++i)
	{
		const auto& dependency = mDependencies[i];
		if (dependency.first == rhs.mpService->GetID() && dependency.second == rhs.mID)
			return true;
	}
	return false;
}

bool Stage::operator < (const Stage& rhs) const
{
	// This stage is 'less' than the rhs if this does not depend on rhs.
	for (int i = 0; i < mDependencies.size(); ++i)
	{
		const auto& dependency = mDependencies[i];
		if (dependency.first == rhs.mpService->GetID() && dependency.second == rhs.mID)
			return false;
	}
	return true;
}