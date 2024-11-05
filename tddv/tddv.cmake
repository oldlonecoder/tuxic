add_executable(tddv.app tddv/tddv.h tddv/tddv.cc)

target_compile_features(tddv.app PUBLIC cxx_std_20)
target_include_directories(tddv.app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(tddv.app tuxic.tools tuxic.lexer tuxic.est tuxic.vision)


install(TARGETS tddv.app
        EXPORT tddv.appTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
