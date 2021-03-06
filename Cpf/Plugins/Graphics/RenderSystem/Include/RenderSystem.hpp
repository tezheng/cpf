//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iRenderSystem.hpp"

namespace CPF
{
	class RenderSystem : public tRefCounted<iRenderSystem>
	{
	public:
		RenderSystem(Plugin::iRegistry*, GOM::iUnknown*);

		// iBase.
		GOM::Result QueryInterface(uint64_t id, void** outIface) override;

		// iStageList.
		GOM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		GOM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		GOM::Result CPF_STDCALL AddStage(MultiCore::iStage* stage) override;
		GOM::Result CPF_STDCALL RemoveStage(MultiCore::StageID id) override;

		GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		GOM::Result CPF_STDCALL GetDependencies(MultiCore::iExecutionPlan* owner, int32_t*, MultiCore::BlockDependency*) override;

		// iSystem.
		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		GOM::Result CPF_STDCALL Configure(MultiCore::iExecutionPlan*) override;

	private:
		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}
