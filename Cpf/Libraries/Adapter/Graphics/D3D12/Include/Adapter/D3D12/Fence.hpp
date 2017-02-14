//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iFence.hpp"
#include "D3D12Utils.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class Fence : public tRefCounted<Graphics::iFence>
			{
			public:
				Fence(Device*, int64_t initValue);
				~Fence() override;

				uint64_t GetValue() const override;
				void WaitFor(uint64_t value) override;

				ID3D12Fence* GetD3DFence() const { return mpFence; }

			private:
				IntrusivePtr<ID3D12Fence> mpFence;
				HANDLE mEvent;
			};
		}
	}
}