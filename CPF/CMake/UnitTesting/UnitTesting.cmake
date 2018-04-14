#
function( MakeUnitTest )
	if (CPF_ENABLE_UNITTESTS)
		if (TARGET gmock)
			set( options )
			set( oneValueArgs LIBRARY GROUP )
			set( multiValueArgs TEST_FILES LINK_LIBRARIES )
			cmake_parse_arguments( MakeUnitTest "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

			add_executable( Test_${MakeUnitTest_LIBRARY} ${MakeUnitTest_TEST_FILES} )
			add_test( NAME Test_${MakeUnitTest_LIBRARY} COMMAND Test_${MakeUnitTest_LIBRARY} )
			target_link_libraries( Test_${MakeUnitTest_LIBRARY} gmock gtest ${MakeUnitTest_LIBRARY} ${MakeUnitTest_LINK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
			target_include_directories( Test_${MakeUnitTest_LIBRARY} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UnitTest> )
			if (MakeUnitTest_GROUP)
				set_property( TARGET Test_${MakeUnitTest_LIBRARY} PROPERTY FOLDER UnitTests/${MakeUnitTest_GROUP} )
			else ()
				set_property( TARGET Test_${MakeUnitTest_LIBRARY} PROPERTY FOLDER UnitTests )
			endif ()
			install( TARGETS Test_${MakeUnitTest_LIBRARY} DESTINATION UnitTests EXPORT Cpf CONFIGURATIONS Release )
		endif ()
	endif ()
endfunction()


#
function( MakeUnitTests )
	if (CPF_ENABLE_UNITTESTS)
		if (TARGET gmock)
			set( options )
			set( oneValueArgs LIBRARY GROUP )
			set( multiValueArgs TEST_FILES LINK_LIBRARIES )
			cmake_parse_arguments( MakeUnitTests "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

			# Figure out if we specified a single library type or intend to do both.
			GetLibraryType(libName libType ${MakeUnitTests_LIBRARY})
			GetTypedLibraries(interfaces interface ${MakeUnitTests_LINK_LIBRARIES})
			GetTypedLibraries(staticLibs static ${MakeUnitTests_LINK_LIBRARIES})
			GetTypedLibraries(sharedLibs shared ${MakeUnitTests_LINK_LIBRARIES})

			if (MakeUnitTests_GROUP)
				set( optGroup GROUP ${MakeUnitTests_GROUP} )
			else()
				set( optGroup "" )
			endif()
			if(libType STREQUAL static)
				MakeUnitTest( ${optGroup} LIBRARY s_${libName} TEST_FILES ${MakeUnitTests_TEST_FILES} LINK_LIBRARIES ${staticLibs} ${interfaces} )
			elseif(libType STREQUAL shared)
				MakeUnitTest( ${optGroup} LIBRARY ${libName} TEST_FILES ${MakeUnitTests_TEST_FILES} LINK_LIBRARIES ${sharedLibs} ${interfaces})
			elseif(libType STREQUAL both)
				MakeUnitTest( ${optGroup} LIBRARY s_${libName} TEST_FILES ${MakeUnitTests_TEST_FILES} LINK_LIBRARIES ${staticLibs} ${interfaces})
				MakeUnitTest( ${optGroup} LIBRARY ${libName} TEST_FILES ${MakeUnitTests_TEST_FILES} LINK_LIBRARIES ${sharedLibs} ${interfaces})
			endif()
		endif ()
	endif ()
endfunction()
