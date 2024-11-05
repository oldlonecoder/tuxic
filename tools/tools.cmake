
set(CMAKE_CXX_STANDARD 20)

message("Entering tools lib configuration:")
include(GNUInstallDirs)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(Target "tools")

message("Current SourceDir:" ${CMAKE_CURRENT_SOURCE_DIR})


add_library("tuxic.${Target}" SHARED
            include/${FRAMEWORK}/${Target}/defs.h
            include/${FRAMEWORK}/${Target}/colors.h     ${Target}/cc/colors.cc
            include/${FRAMEWORK}/${Target}/glyphes.h    ${Target}/cc/glyphes.cc
            include/${FRAMEWORK}/${Target}/cadres.h     ${Target}/cc/cadres.cc
            include/${FRAMEWORK}/${Target}/string.h     ${Target}/cc/string.cc
#            include/${FRAMEWORK}/${Target}/geometry.h src/tools/geometry.cc
#            include/${FRAMEWORK}/${Target}/tools/cmdargs.h src/tools/cmdargs.cc
#            include/${FRAMEWORK}/${Target}/tools/sscan.h src/tools/sscan.cc
#            include/${FRAMEWORK}/${Target}/object.h src/tools/object.cc
#            include/${FRAMEWORK}/${Target}/actions.h
#            # include/${BaseTarget}/ui/widget.input_track.h src/ui/widget/input_track.cc
#            # include/${BaseTarget}/ui/widget/statusbar.h src/ui/widget/statusbar.cc
#            include/${FRAMEWORK}/${Target}/journal/book.h src/journal/book.cc
#
#            include/${FRAMEWORK}/${Target}/lexer/lexer_types.h       src/lexer/lexer_types.cc
#            include/${FRAMEWORK}/${Target}/lexer/token_data.h        src/lexer/token_data.cc
#            include/${FRAMEWORK}/${Target}/lexer/tokens_table.h      src/lexer/tokens_table.cc
#            include/${FRAMEWORK}/${Target}/lexer/lexer.h             src/lexer/lexer.cc
#            include/${FRAMEWORK}/${Target}/est/alu.h                 src/est/alu.cc
#            include/${FRAMEWORK}/${Target}/est/node.h                src/est/node.cc
#            include/${FRAMEWORK}/${Target}/est/variable.h            src/est/variable.cc
#            include/${FRAMEWORK}/${Target}/est/bloc.h                src/est/bloc.cc
#            include/${FRAMEWORK}/${Target}/est/expression.h          src/est/expression.cc
#            include/${FRAMEWORK}/${Target}/ui/globals.h              src/ui/globals.cc
#            include/${FRAMEWORK}/${Target}/ui/terminal.h             src/ui/terminal.cc
#            include/tuxvision/ui/vchar.h                    src/ui/terminal.vchar.cc
#            include/${FRAMEWORK}/${Target}/ui/events.h               src/ui/events.cc
#            include/${FRAMEWORK}/${Target}/ui/application.h          src/ui/application.cc
#            include/${FRAMEWORK}/${Target}/ui/widget.h               src/ui/widget.cc src/ui/widget_painter.cc
#            include/${FRAMEWORK}/${Target}/ui/widget/label.h         src/ui/widget/label.cc
#            include/${FRAMEWORK}/${Target}/ui/widget/window.h        src/ui/widget/window.cc
#            include/${FRAMEWORK}/${Target}/ui/widget/uiscreen.h      src/ui/widget/uiscreen.cc
#            include/${FRAMEWORK}/${Target}/ui/widget/status_bar.h    src/ui/widget/status_bar.cc

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


target_link_libraries("tuxic.${Target}" ${CMAKE_DL_LIBS}) # and other system dependencies...








install(DIRECTORY
        include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)


add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
    install_manifest.txt to be uninstalled!
)
# Enable packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME "tuxic.${Target}")
set(CPACK_GENERATOR "TGZ")

# Include CPack
#include(CPack) # Scrap!! No way to include header files!
