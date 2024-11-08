

option(BUILD_TOOLS "Enable building (personal) Utility Tools library - Required" 	ON)
option(BUILD_LEXER "Enable building the Lexer & Tokens Library" 					ON)
option(BUILD_EST "Enable building EST ([Arithmetic] Expression Syntax Tree) library" ON)
option(BUILD_VISION  "Enable building the Vision (Ansi Text UI) library" 			ON)
option(BUILD_TDDV "Build the tests application" 									ON)

SET(TUXIC_ROOT 			${CMAKE_CURRENT_SOURCE_DIR})
SET(TOOLS_INCLUDE_DIR 	${TUXIC_ROOT}/include/tools})
SET(LEXER_INCLUDE_DIR 	${TUXIC_ROOT}/include/lexer})
SET(EST_INCLUDE_DIR 	${TUXIC_ROOT}/include/est})
SET(VISION_INCLUDE_DIR 	${TUXIC_ROOT}/include/vision})


if(BUILD_TOOLS)
    include(tools/tools.cmake)
endif()



if(BUILD_LEXER)
    include(lexer/lexer.cmake)
endif()

if(BUILD_EST)
    include(est/est.cmake)
endif()

if(BUILD_VISION)
    include(vision/vision.cmake)
endif()


if(BUILD_TDDV)
    include(tddv/tddv.cmake)
endif()


message ("Project SourceDir:" ${PROJECT_SOURCE_DIR})


IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()




# uninstall target
#if(NOT TARGET uninstall)
#  configure_file(
#    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
#    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
#    IMMEDIATE @ONLY)
#
#  add_custom_target(uninstall
#    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
#endif()
