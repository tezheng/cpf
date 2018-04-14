function (add_library name)
	get_property (allLibraries GLOBAL PROPERTY ALL_LIBRARIES)
	LIST (APPEND allLibraries ${name})
	set_property (GLOBAL PROPERTY ALL_LIBRARIES ${allLibraries})
	_add_library (${ARGV})
endfunction (add_library)
