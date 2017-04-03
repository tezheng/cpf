//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iPipeline.hpp"
#include "Plugin/iClassInstance.hpp"
#include "UnorderedMap.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A multicore processing pipeline. */
		class Pipeline : public tRefCounted<iPipeline>
		{
		public:
			Pipeline();
			~Pipeline();

			COM::Result QueryInterface(COM::InterfaceID id, void** iface) override;
			iSystem* CPF_STDCALL Install(iSystem*) override;
			COM::Result CPF_STDCALL Remove(iSystem*) override;
			COM::Result CPF_STDCALL Configure() override;
			COM::Result CPF_STDCALL GetSystem(SystemID id, iSystem**) const override;
			COM::Result CPF_STDCALL GetSystem(const char* const, iSystem**) const override;
			COM::Result CPF_STDCALL GetStage(SystemID systemID, StageID stageID, iStage**) override;
			void CPF_STDCALL Submit(Concurrency::Scheduler*) override;
			COM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) override;
			COM::Result CPF_STDCALL GetSystems(int32_t* count, iSystem**) override;

		private:
			bool _ConfigureSystems() const;

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<iSystem>>;
			SystemMap mSystemMap;

			Concurrency::Scheduler::Queue mQueue;
#ifdef CPF_DEBUG
			bool mChanged;
#endif
			Vector<String> mQueueInfo;
		};


		/** @brief Class instance object for registry installation. */
		class PipelineClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new Pipeline();
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
