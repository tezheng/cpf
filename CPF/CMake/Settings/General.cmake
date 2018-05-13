#
message ("Setting up compiler: ${CPF_COMPILER_NAME} ${CPF_COMPILER_VERSION_MAJOR} - ${CPF_COMPILER_VERSION_MINOR}")

preferred_include (
	"${CMAKE_CURRENT_LIST_DIR}/Detail/${CPF_COMPILER_NAME}_General_${CPF_COMPILER_VERSION_MAJOR}-${CPF_COMPILER_VERSION_MINOR}.cmake"
	"${CMAKE_CURRENT_LIST_DIR}/Detail/${CPF_COMPILER_NAME}_General_${CPF_COMPILER_VERSION_MAJOR}-0.cmake"
)