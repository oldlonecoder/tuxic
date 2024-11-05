
set(CMAKE_CXX_STANDARD 20)

message("Entering tools lib configuration:")
include(GNUInstallDirs)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(Target "vision")

message("Current SourceDir:" ${CMAKE_CURRENT_SOURCE_DIR})


add_library("tuxic.${Target}" SHARED
            include/${FRAMEWORK}/${Target}/tuxns.h ${Target}/cc/tuxns.cc
            include/${FRAMEWORK}/${Target}/terminal.h ${Target}/cc/terminal.cc
            include/${FRAMEWORK}/${Target}/vchar.h ${Target}/cc/terminal.vchar.cc
            include/${FRAMEWORK}/${Target}/events.h ${Target}/cc/events.cc
            include/${FRAMEWORK}/${Target}/application.h ${Target}/cc/application.cc

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


target_link_libraries("tuxic.${Target}" ${CMAKE_DL_LIBS} tuxic.tools tuxic.lexer tuxic.est) # and other system dependencies...



install(TARGETS ${FRAMEWORK}.${Target}
        EXPORT "${FRAMEWORK}.${Target}"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)





install(DIRECTORY
        include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)


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
