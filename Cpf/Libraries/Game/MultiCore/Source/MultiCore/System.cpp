//////////////////////////////////////////////////////////////////////////
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/iPipeline.hpp"
#include "System.hpp"
#include "UnorderedMap.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

System::System()
	: mpOwner(nullptr)
{
}

System::~System()
{}

COM::Result CPF_STDCALL System::Initialize(Plugin::iRegistry* rgy, iPipeline* owner, const char* name)
{
	(void)rgy;
	if (owner && name)
	{
		mpOwner = owner;
		mID = SystemID(name, strlen(name));
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL System::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}


iPipeline* CPF_STDCALL System::GetOwner() const
{
	return mpOwner;
}

COM::Result CPF_STDCALL System::GetStage(StageID id, iStage** outStage) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			*outStage = stage;
			return COM::kOK;
		}
	}
	return COM::kInvalid;
}

COM::Result CPF_STDCALL System::GetInstructions(int32_t* count, Instruction* instructions)
{
	if (count)
	{
		Instructions result;
		for (const auto& stage : mStages)
		{
			if (stage->IsEnabled())
			{
				int32_t instructionCount = 0;
				stage->GetInstructions(GetID(), &instructionCount, nullptr);
				Vector<Instruction> instrs(instructionCount);
				stage->GetInstructions(GetID(), &instructionCount, instrs.data());
				result.insert(result.end(), instrs.begin(), instrs.end());
			}
		}
		if (instructions)
		{
			if (*count >= result.size())
			{
				int32_t index = 0;
				for (auto& inst : result)
					instructions[index++] = inst;
				return COM::kOK;
			}
			return COM::kNotEnoughSpace;
		}
		*count = int32_t(result.size());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool System::AddStage(iStage* stage)
{
	if (stage && stage->IsEnabled())
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return true;
	}
	return false;
}

bool System::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return true;
		}
	}
	return false;
}

SystemID CPF_STDCALL System::GetID() const
{
	return mID;
}

void CPF_STDCALL System::AddDependency(BlockDependency dep)
{
	mDependencies.push_back(dep);
}

COM::Result CPF_STDCALL System::GetDependencies(int32_t* count, BlockDependency* deps)
{
	if (count)
	{
		BlockDependencies result;
		for (const auto& dep : mDependencies)
		{
			iStage* depStage = nullptr;
			GetOwner()->GetStage(dep.mDependent.mSystem, dep.mDependent.mStage, &depStage);
			iStage* targetStage = nullptr;
			GetOwner()->GetStage(dep.mTarget.mSystem, dep.mTarget.mStage, &targetStage);
			if (depStage && depStage->IsEnabled() &&
				targetStage && targetStage->IsEnabled())
			{
				result.push_back(dep);
			}
			else
			{
				CPF_LOG(MultiCore, Info) << "Dropped disabled dependency.";
			}
		}

		if (deps)
		{
			int32_t index = 0;
			for (const auto& dep : result)
				deps[index++] = dep;
			return COM::kOK;
		}
		else
		{
			*count = int32_t(result.size());
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
namespace
{
	using SystemMap = UnorderedMap<SystemID, System::Creator>;
	SystemMap s_SystemMap;
}

iSystem* iSystem::_Create(Plugin::iRegistry* rgy, iPipeline* owner, SystemID id, const char* name, const Desc* desc)
{
	auto it = s_SystemMap.find(id);
	if (it != s_SystemMap.end())
		return (*it->second)(rgy, owner, name, desc);
	return nullptr;
}

bool iSystem::Install(SystemID id, Creator creator)
{
	if (s_SystemMap.find(id) != s_SystemMap.end())
		return false;
	s_SystemMap[id] = creator;
	return true;
}

bool iSystem::Remove(SystemID id)
{
	if (s_SystemMap.find(id) == s_SystemMap.end())
		return false;
	s_SystemMap.erase(id);
	return true;
}
