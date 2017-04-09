//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "IO/Stream.hpp"
#include "Graphics/WindingOrder.hpp"
#include "Graphics/CullMode.hpp"
#include "Graphics/RasterizerStateDesc.hpp"
#include "Graphics/TopologyType.hpp"
#include "Graphics/DepthStencilDesc.hpp"
#include "Graphics/InputLayoutDesc.hpp"
#include "Graphics/PipelineStateDesc.hpp"
#include "Graphics/ShaderType.hpp"
#include "Graphics/ParamVisibility.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/iImageView.hpp"
#include "Math/Vector4v.hpp"
#include "Math/Matrix44v.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;
using namespace Platform;


bool ExperimentalD3D12::_CreateResources()
{
	// Create shaders.
	{
		IO::Stream* vertexShaderHlsl = mpLocator->Open(RESOURCE_ID("shaders/", "basic_vs.hlsl"));
		IO::Stream* pixelShaderHlsl = mpLocator->Open(RESOURCE_ID("shaders/", "basic_ps.hlsl"));
		IntrusivePtr<BinaryBlob> vertexShaderByteCode;
		{
			auto vertexShaderSrc = ReadText(vertexShaderHlsl);
			mpDevice->CompileToByteCode("main", ShaderType::eVertex, vertexShaderSrc.size(), vertexShaderSrc.data(), vertexShaderByteCode.AsTypePP());
		}
		mpDevice->CreateShader(vertexShaderByteCode, mpVertexShader.AsTypePP());

		IntrusivePtr<BinaryBlob> pixelShaderByteCode;
		{
			auto pixelShaderSrc = ReadText(pixelShaderHlsl);
			mpDevice->CompileToByteCode("main", ShaderType::ePixel, pixelShaderSrc.size(), pixelShaderSrc.data(), pixelShaderByteCode.AsTypePP());
		}
		mpDevice->CreateShader(pixelShaderByteCode, mpPixelShader.AsTypePP());
	}

	//////////////////////////////////////////////////////////////////////////
	// Create pipeline.
	PipelineStateDesc pipelineDesc = PipelineStateDesc::Build()
		.VertexShader(mpVertexShader)
		.PixelShader(mpPixelShader)
		.Topology(TopologyType::eTriangle)

		.Rasterizer(RasterizerStateDesc::Build()
			.CullMode(CullMode::eBack)
			.WindingOrder(WindingOrder::eClockwise)
			.DepthClipping(false)
		)
		.DepthStencil(DepthStencilStateDesc::Build()
			.DepthTest(true)
			.DepthWriteMask(DepthWriteMask::eAll)
		)
		.TargetBlend(0, RenderTargetBlendStateDesc::Build()
			.Blending(false)
			.Src(BlendFunc::eSrcAlpha)
			.Dst(BlendFunc::eOne)
			.Op(BlendOp::eAdd)
			.SrcAlpha(BlendFunc::eOne)
			.DstAlpha(BlendFunc::eZero)
			.OpAlpha(BlendOp::eAdd)
		)
		.InputLayout(
		{
			ElementDesc("POSITION", Format::eRGB32f),
			ElementDesc("COLOR", Format::eRGBA32f),
			ElementDesc("TRANSLATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
			ElementDesc("SCALE", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
			ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
			ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1),
			ElementDesc("ORIENTATION", Format::eRGB32f, InputClassification::ePerInstance, 1).Slot(1)
		})
		.RenderTargets({ Format::eRGBA8un })
		.DepthStencilFormat(Format::eD32f)
		;

	//////////////////////////////////////////////////////////////////////////
	ResourceBindingDesc bindingState({
		ParamConstantBuffer(0, ParamVisibility::eVertex)
	});
	mpDevice->CreateResourceBinding(&bindingState, mpResourceBinding.AsTypePP());
	mpDevice->CreatePipeline(&pipelineDesc, mpResourceBinding, mpPipeline.AsTypePP());

	//////////////////////////////////////////////////////////////////////////
	struct PosColor
	{
		Vector3f mPosition;
		Vector4f mColor;
	};

	// Create the test data.
#define SS 1.0f
#define P0 { -SS, -SS, -SS }
#define P1 { +SS, -SS, -SS }
#define P2 { +SS, +SS, -SS }
#define P3 { -SS, +SS, -SS }
#define P4 { -SS, -SS, +SS }
#define P5 { +SS, -SS, +SS }
#define P6 { +SS, +SS, +SS }
#define P7 { -SS, +SS, +SS }
#define CC0 { 0.2f, 0.5f, 0.2f, 0.03f }
#define CC1 { 0.2f, 0.2f, 0.5f, 0.03f }
#define CC2 { 0.2f, 0.2f, 0.5f, 0.03f }
#define CC3 { 0.5f, 0.5f, 0.2f, 0.03f }
	PosColor vbData[] =
	{
		// Front face. 0-3  +Z
		{ P7,CC0 },
		{ P6,CC1 },
		{ P5,CC2 },
		{ P4,CC3 },

		// Back face. 4-7  -Z
		{ P0,CC0 },
		{ P1,CC1 },
		{ P2,CC2 },
		{ P3,CC3 },

		// Left face. 8-11  -X
		{ P7,CC0 },
		{ P3,CC1 },
		{ P0,CC2 },
		{ P4,CC3 },

		// Right face. 12-15  +X
		{ P2,CC0 },
		{ P6,CC1 },
		{ P5,CC2 },
		{ P1,CC3 },

		// Top face. 16-19  +Y
		{ P6,CC0 },
		{ P2,CC1 },
		{ P3,CC2 },
		{ P7,CC3 },

		// Bottom face. 20-23  -Y
		{ P1,CC0 },
		{ P5,CC1 },
		{ P4,CC2 },
		{ P0,CC3 },
	};
	uint32_t ibData[] =
	{
		0, 2, 1, 0, 3, 2,
		4, 7, 6, 4, 6, 5,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	// Create a vertex buffer.
	mpDevice->CreateVertexBuffer(BufferUsage::eImmutable, sizeof(vbData), sizeof(PosColor), vbData, mpVertexBuffer.AsTypePP());
	for (int i = 0; i < mBackBufferCount; ++i)
		mpDevice->CreateVertexBuffer(BufferUsage::eDynamic, sizeof(Instance) * kInstanceCount, sizeof(Instance), nullptr, mpInstanceBuffer[i].AsTypePP());

	// Create an index buffer.
	mpDevice->CreateIndexBuffer(Format::eR32u, BufferUsage::eDefault, sizeof(ibData), ibData, mpIndexBuffer.AsTypePP());

	// Create a the view projection constant buffer.
	struct CameraProj
	{
		Matrix44fv mView;
		Matrix44fv mInvView;
		Matrix44fv mProjection;
		float mNear;
		float mFar;
	} initCameraData
	{
		Transpose(Matrix44fv::LookAt(Vector3fv(0.0f, 180.0f, 400.0f), Vector3fv(0.0f), Vector3fv(0.0f, 1.0f, 0.0f))),
		Matrix44fv::Identity(),
		Transpose(Matrix44fv::PerspectiveLH(
			2.0f * mViewportSize * mAspectRatio,
			2.0f * mViewportSize,
			1.0f, 1000.0f,
			0.0f, 1.0f
		)),
		1.0f, 1000.0f
	};
	mpDevice->CreateConstantBuffer(sizeof(CameraProj), &initCameraData, mpViewProj.AsTypePP());

	return false;
}

void ExperimentalD3D12::_DestroyResources()
{
	// Guarantee shutdown order.
	mpVertexShader.Assign(nullptr);
	mpPixelShader.Assign(nullptr);
	mpVertexBuffer.Assign(nullptr);
	for (int i = 0; i < mBackBufferCount; ++i)
	{
		mpInstanceBuffer[i].Assign(nullptr);
		mpPreCommandBuffer[i].Assign(nullptr);
		mpPreCommandPool[i].Assign(nullptr);
		mpPostCommandBuffer[i].Assign(nullptr);
		mpPostCommandPool[i].Assign(nullptr);
	}
	mpIndexBuffer.Assign(nullptr);
	mpViewProj.Assign(nullptr);
	mpPipeline.Assign(nullptr);
	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();
	mpSwapChain.Assign(nullptr);
	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();
	mpFence.Assign(nullptr);
	mpResourceBinding.Assign(nullptr);

	mScheduler.Shutdown();
	for (auto& data : mWorkerData)
	{
		for (int i = 0; i < mBackBufferCount; ++i)
		{
			data.mpCommandPool[i].Assign(nullptr);
			data.mpCommandBuffer[i].Assign(nullptr);
		}
	}
	mpDevice.Assign(nullptr);
}
