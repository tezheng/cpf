function(CPF_GEN_GOM outList target ext outDir)
	set (genFiles "")
	foreach (file ${ARGN})
		get_filename_component(fileName ${file} NAME_WE)
		set (targetFile "${outDir}/${fileName}.${ext}")

		add_custom_command (OUTPUT ${targetFile}
			DEPENDS ${file}
			COMMAND ${CPF_OS_BIN_DIR}/IDL --${target}
				--input="${file}"
				--output="${targetFile}"
		)
		LIST (APPEND genFiles ${targetFile})
	endforeach()
	set (${outList} "${genFiles}" PARENT_SCOPE)
endfunction(CPF_GEN_GOM)