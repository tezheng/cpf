#
configure_file (Include/Configuration/Setup.hpp.in
	${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}/Configuration/Setup.hpp )


#
set (INCLUDE_FILES
	Include/Configuration.hpp
	Include/Configuration/Setup.hpp.in
	Include/Configuration/Assert.hpp
)
set (INCLUDE_FILES_PLATFORM
	${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}/Configuration/Setup.hpp
	Include/${CPF_TARGET_PLATFORM}/Configuration/Platform/DebugBreak.hpp
	Include/${CPF_TARGET_PLATFORM}/Configuration/Platform/OSSetup.hpp
)
set (INCLUDE_FILES_COMPILER
	Include/${CPF_COMPILER_NAME}/Configuration/Compiler/ImportExport.hpp
	Include/${CPF_COMPILER_NAME}/Configuration/Compiler/Alignment.hpp
)


add_library (Configuration INTERFACE)
target_include_directories (Configuration
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_PLATFORM}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_COMPILER_NAME}>
)

add_custom_target (Configuration_IDE SOURCES ${INCLUDE_FILES} ${INCLUDE_FILES_PLATFORM} ${INCLUDE_FILES_COMPILER})
set_property (TARGET Configuration_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Platform FILES ${INCLUDE_FILES_PLATFORM})
source_group (Interface\\Compiler FILES ${INCLUDE_FILES_COMPILER})


# Installation setup.
install (DIRECTORY Include/Configuration
	DESTINATION Include/Configuration
	PATTERN *
)

install (DIRECTORY ${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}
	DESTINATION ${CPF_PLATFORM_INCLUDE_DIR}
	PATTERN *
)

install( TARGETS Configuration
	EXPORT CoreConfiguration
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

install( EXPORT CoreConfiguration DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY Configuration GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
