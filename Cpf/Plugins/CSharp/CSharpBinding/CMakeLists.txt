set (INTERFACE_FILES
	Interface/IPlugin.hpp
)

add_library (i_CSharpBindings INTERFACE)
target_include_directories (i_CSharpBindings
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

# ###############################################
set (INCLUDE_FILES
	Include/CSharpBindings.hpp
)
set (SOURCE_FILES
	Source/CSharpBindings.cpp
	Source/AssemblyInfo.cpp
)

add_library (CSharpBindings SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
	${INTERFACE_FILES}
)
target_link_libraries (CSharpBindings i_CSharpBindings Plugin)
target_compile_definitions (CSharpBindings PUBLIC _WINDLL _UNICODE UNICODE)
target_include_directories (CSharpBindings
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
set_property (TARGET CSharpBindings PROPERTY FOLDER Plugins/CSharp)

MakeUnitTest (LIBRARY CSharpBindings GROUP CSharp
	TEST_FILES
		UnitTest/Test_All.hpp
		../../../Libraries/Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_IO s_PluginHost i_TestCSharp
)


# ###############################################
target_compile_options(CSharpBindings PRIVATE /clr)
target_compile_options(CSharpBindings PRIVATE /Fa$(IntDir))
target_compile_options(CSharpBindings PRIVATE /fp:precise)
set_property(TARGET CSharpBindings PROPERTY VS_GLOBAL_ROOTNAMESPACE CSharpBindings)
set_property(TARGET CSharpBindings PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")
set_property(TARGET CSharpBindings PROPERTY VS_GLOBAL_CLRSupport "true")
set_property(TARGET CSharpBindings PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")

set_property(TARGET CSharpBindings PROPERTY VS_DOTNET_REFERENCES
	"mscorlib"
	"System"
	"System.Core"
	"System.Data"
	"System.Xml"
	"System.Runtime.InteropServices"
)

set_target_properties (CSharpBindings PROPERTIES LINK_FLAGS_DEBUG "/ASSEMBLYDEBUG")
set_target_properties (CSharpBindings PROPERTIES LINK_FLAGS_DEBUG "/ASSEMBLYDEBUG")
string (REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string (REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string (REPLACE "/GR-" "/GR" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
