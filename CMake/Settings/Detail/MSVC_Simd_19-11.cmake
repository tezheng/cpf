#
if (CPF_SIMD_INSTRUCTION_SET STREQUAL "SSE")
	if (CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Reference")
		set (CPF_SIMD_INSTRUCTION_SET "None")
	elseif (CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse1" OR
			CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse2")
		set (INSTRUCTION_SET_FLAG "")
	elseif (CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse3" OR
			CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse4" OR
			CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse4_1" OR
			CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse4_2" OR
			CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Sse4a")
		set (INSTRUCTION_SET_FLAG "")
	elseif (CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Avx")
		set (INSTRUCTION_SET_FLAG "/arch:AVX")
	elseif (CPF_SIMD_INSTRUCTION_LEVEL STREQUAL "Avx2")
		set (INSTRUCTION_SET_FLAG "/arch:AVX2")
	else ()
		message (WARNING "Unknown simd configuration, using Reference.")
		set (CPF_SIMD_INSTRUCTION_SET "None")
		set (CPF_SIMD_INSTRUCTION_LEVEL "Reference")
		set (INSTRUCTION_SET_FLAG "")
	endif ()
else ()
	# TODO: Arm and others...
endif ()


#
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${INSTRUCTION_SET_FLAG}" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${INSTRUCTION_SET_FLAG}" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${INSTRUCTION_SET_FLAG}" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${INSTRUCTION_SET_FLAG}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${INSTRUCTION_SET_FLAG}" CACHE STRING "" FORCE)
