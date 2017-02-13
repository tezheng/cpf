# Setup the language dialect in use.
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CPF_CPP_DIALECT} -stdlib=libc++" )

IF( CMAKE_GENERATOR STREQUAL Xcode )
	SET( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD ${CPF_CPP_DIALECT} )
	SET( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++" )
ENDIF()
