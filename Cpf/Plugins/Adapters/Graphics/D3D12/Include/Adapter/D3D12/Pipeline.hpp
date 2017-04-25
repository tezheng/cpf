//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/iPipeline.hpp"
#include "D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct PipelineStateDesc;
		struct iPipeline;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;
			class ResourceBinding;


			class Pipeline : public tRefCounted<Graphics::iPipeline>
			{
			public:
				Pipeline(Device*, const Graphics::PipelineStateDesc*, const ResourceBinding* CPF_GFX_DEBUG_PARAM_DECL);
				virtual ~Pipeline();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				ID3D12PipelineState* GetPipelineState() const { return mpPipelineState; }

			private:
				IntrusivePtr<ID3D12PipelineState> mpPipelineState;
			};
		}
	}
}