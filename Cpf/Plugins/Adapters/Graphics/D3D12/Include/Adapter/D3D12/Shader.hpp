//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Graphics/iShader.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"


namespace CPF
{
	namespace Graphics
	{
		struct iDevice;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class Shader : public tRefCounted<Graphics::iShader>
			{
			public:
				Shader();
				virtual ~Shader();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				bool LoadFrom(Graphics::iDevice* device, Graphics::iBlob*) override;

				D3D12_SHADER_BYTECODE GetByteCode() const;

			private:
				D3D12_SHADER_BYTECODE mByteCode;
			};
		}
	}
}
