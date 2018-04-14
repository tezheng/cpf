macro(CheckValue inValue checkValue trueValue falseValue)
	set(args "${ARGN}")
	if(${inValue} STREQUAL ${checkValue})
		foreach(arg IN LISTS args)
			set(${arg} ${trueValue})
		endforeach()
	else()
		foreach(arg IN LISTS args)
			set(${arg} ${falseValue})
		endforeach()
	endif()
endmacro()


macro(CheckInclusiveValue inValue trueValue falseValue checkVals outVals)
	set( cv "${checkVals}" )
	set( ov "${outVals}" )
	list(FIND cv ${inValue} indexVal)

	if(indexVal EQUAL -1)
		foreach(arg IN LISTS ov)
			set( ${arg} 0 )
		endforeach()
	else()
		foreach(val RANGE 0 ${indexVal})
			list(GET ov ${val} var)
			set(${var} ${trueValue})
		endforeach()

		list(LENGTH ov count)
		math(EXPR count ${count}-1)
		math(EXPR indexVal ${indexVal}+1)

		if(NOT ${indexVal} GREATER ${count} )
			foreach(val RANGE ${indexVal} ${count})
				list(GET ov ${val} var)
				set(${var} ${falseValue})
			endforeach()
		endif()
	endif()
endmacro()
