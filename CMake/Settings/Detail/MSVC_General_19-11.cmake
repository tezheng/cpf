#
set (CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /MP /GF /GR- /EHsc /volatile:iso /W4 /wd4324 /wd4201" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /GS-" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_MINSIZEREL "/DNDEBUG /MD /GS-" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /favor:blend /MD /GS- /Gw /Gy /GL" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /GS- /Zi" CACHE STRING "" FORCE)

set (CMAKE_EXE_LINKER_FLAGS "/machine:x64" CACHE STRING "" FORCE)
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG" CACHE STRING "" FORCE)

set (CMAKE_MODULE_LINKER_FLAGS "/machine:x64" CACHE STRING "" FORCE)
set (CMAKE_MODULE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG" CACHE STRING "" FORCE)

set (CMAKE_SHARED_LINKER_FLAGS "/machine:x64" CACHE STRING "" FORCE)
set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG" CACHE STRING "" FORCE)

set (CMAKE_STATIC_LINKER_FLAGS "/machine:x64" CACHE STRING "" FORCE)
set (CMAKE_STATIC_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG" CACHE STRING "" FORCE)

# Customize the configuration.
set (CPF_COMPILER_HAS_ALIGNAS ON)
