# ###############################################
set( CPF_COMPILER_NAME "MSVC" )

string( REGEX MATCH "([0-9]+)\.([0-9]+)\.([0-9]+)" CPF_COMPILER_VERSION "${CMAKE_C_COMPILER_VERSION}" )
set( CPF_COMPILER_VERSION_MAJOR ${CMAKE_MATCH_1} )
set( CPF_COMPILER_VERSION_MINOR ${CMAKE_MATCH_2} )
set( CPF_COMPILER_VERSION_PATCH ${CMAKE_MATCH_3} )

add_definitions( -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS )
add_definitions( -D_SCL_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS )
