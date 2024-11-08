
set(CMAKE_CXX_STANDARD 20)

message("Entering tools lib configuration:")
include(GNUInstallDirs)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(Target "est")

message("Current SourceDir:" ${CMAKE_CURRENT_SOURCE_DIR})


add_library("tuxic.${Target}" SHARED
            include/${FRAMEWORK}/${Target}/alu.h ${Target}/cc/alu.cc
            include/${FRAMEWORK}/${Target}/node.h ${Target}/cc/node.cc
            include/${FRAMEWORK}/${Target}/variable.h ${Target}/cc/variable.cc
            include/${FRAMEWORK}/${Target}/bloc.h ${Target}/cc/bloc.cc
            include/${FRAMEWORK}/${Target}/expression.h ${Target}/cc/expression.cc
            ../tddv/tddv.cc
            ../tddv/tddv.h
)


target_include_directories("tuxic.${Target}" PUBLIC
                           "$<BUILD_INTERFACE:${TUXIC_ROOT}/include>"
                           $<INSTALL_INTERFACE:include>
)

target_compile_definitions("tuxic.${Target}" PUBLIC "tuxic.${Target}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header("tuxic.${Target}" EXPORT_FILE_NAME ${tuxic.${Target}_export})

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()


target_link_libraries("tuxic.${Target}" ${CMAKE_DL_LIBS} tuxic.tools tuxic.lexer) # and other system dependencies...


install(DIRECTORY
        include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)

install(TARGETS ${FRAMEWORK}.${Target}
        EXPORT "${FRAMEWORK}.${Target}"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

#add_custom_target("uninstall" COMMENT "Uninstall installed files")
#add_custom_command(
#    TARGET "uninstall"
#    POST_BUILD
#    COMMENT "Uninstall files with install_manifest.txt"
#    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
#    install_manifest.txt to be uninstalled!
#)
## Enable packaging
#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PACKAGE_NAME "tuxic.${Target}")
#set(CPACK_GENERATOR "TGZ")

# Include CPack
#include(CPack) # Scrap!! No way to include header files!
