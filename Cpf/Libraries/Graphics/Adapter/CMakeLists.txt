# ###############################################
set (INCLUDE_GRAPHICS_FILES
	Include/Graphics/BinaryBlob.hpp
	Include/Graphics/BlendFunc.hpp
	Include/Graphics/BlendOp.hpp
	Include/Graphics/ComparisonFunc.hpp
	Include/Graphics/ConservativeRasterization.hpp
	Include/Graphics/CullMode.hpp
	Include/Graphics/DepthWriteMask.hpp
	Include/Graphics/Driver.hpp
	Include/Graphics/FillMode.hpp
	Include/Graphics/Format.hpp
	Include/Graphics/IndexStripCut.hpp
	Include/Graphics/LogicOp.hpp
	Include/Graphics/TopologyType.hpp
	Include/Graphics/Ratio.hpp
	Include/Graphics/StencilOp.hpp
	Include/Graphics/WindingOrder.hpp
	Include/Graphics/BufferUsage.hpp
)
set (INCLUDE_GRAPHICS_DESCRIPTORS
	Include/Graphics/Descriptors/BlendStateDesc.hpp
	Include/Graphics/Descriptors/DepthStencilDesc.hpp
	Include/Graphics/Descriptors/InputLayoutDesc.hpp
	Include/Graphics/Descriptors/PipelineStateDesc.hpp
	Include/Graphics/Descriptors/RasterizerStateDesc.hpp
	Include/Graphics/Descriptors/SampleDesc.hpp
	Include/Graphics/Descriptors/ResourceBindingDesc.hpp
	Include/Graphics/Descriptors/ResourceDesc.hpp
)
set (INCLUDE_GRAPHICS_INTERFACES
	Include/Graphics/Interfaces/iAdapter.hpp
	Include/Graphics/Interfaces/iCommandBuffer.hpp
	Include/Graphics/Interfaces/iCommandPool.hpp
	Include/Graphics/Interfaces/iDevice.hpp
	Include/Graphics/Interfaces/iImage.hpp
	Include/Graphics/Interfaces/iImageView.hpp
	Include/Graphics/Interfaces/iInstance.hpp
	Include/Graphics/Interfaces/iSampler.hpp
	Include/Graphics/Interfaces/iSwapChain.hpp
	Include/Graphics/Interfaces/iOutput.hpp
	Include/Graphics/Interfaces/iFence.hpp
	Include/Graphics/Interfaces/iShader.hpp
	Include/Graphics/Interfaces/iPipeline.hpp
	Include/Graphics/Interfaces/iResourceBinding.hpp
	Include/Graphics/Interfaces/iResource.hpp
	Include/Graphics/Interfaces/iIndexBuffer.hpp
	Include/Graphics/Interfaces/iVertexBuffer.hpp
	Include/Graphics/Interfaces/iConstantBuffer.hpp
	Include/Graphics/Interfaces/iDescriptorPool.hpp
)
set (SOURCE_GRAPHICS_FILES
	Source/BinaryBlob.cpp
	Source/Driver.cpp
	Source/Format.cpp
	Source/Ratio.cpp
)
set (SOURCE_GRAPHICS_DESCRIPTORS
	Source/Descriptors/BlendStateDesc.cpp
	Source/Descriptors/DepthStencilDesc.cpp
	Source/Descriptors/InputLayoutDesc.cpp
	Source/Descriptors/PipelineStateDesc.cpp
	Source/Descriptors/RasterizerStateDesc.cpp
	Source/Descriptors/SampleDesc.cpp
	Source/Descriptors/ResourceBindingDesc.cpp
	Source/Descriptors/ResourceDesc.cpp
)

# ###############################################
add_library (s_GraphicsDriver STATIC
	${INCLUDE_GRAPHICS_FILES}
	${INCLUDE_GRAPHICS_DESCRIPTORS}
	${INCLUDE_GRAPHICS_INTERFACES}
	${SOURCE_GRAPHICS_FILES}
	${SOURCE_GRAPHICS_DESCRIPTORS}
)

# ###############################################
target_compile_definitions (s_GraphicsDriver
	PUBLIC CPF_STATIC_GRAPHICS_ADAPTER
	PRIVATE CPF_BUILD_GRAPHICS_ADAPTER
)
target_include_directories (s_GraphicsDriver
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_GraphicsDriver
	LINK_PUBLIC
		Configuration s_RefCount s_Math s_IO Logging
)

# ###############################################
set_property (TARGET s_GraphicsDriver
	PROPERTY FOLDER Libraries/Static/Graphics
)

# ###############################################
source_group (Headers\\Graphics FILES ${INCLUDE_GRAPHICS_FILES})
source_group (Headers\\Graphics\\Descriptors FILES ${INCLUDE_GRAPHICS_DESCRIPTORS})
source_group (Headers\\Graphics\\Interfaces FILES ${INCLUDE_GRAPHICS_INTERFACES})
source_group (Sources\\Graphics FILES ${SOURCE_GRAPHICS_FILES})
source_group (Sources\\Graphics\\Descriptors FILES ${SOURCE_GRAPHICS_DESCRIPTORS})

# ###############################################
install (TARGETS s_GraphicsDriver
	EXPORT GraphicsDriverConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)


# ###############################################
install (EXPORT GraphicsDriverConfig DESTINATION CMake)