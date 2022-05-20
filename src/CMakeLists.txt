add_executable(test test.c)

target_link_libraries(test libEGL libGLESv2 SDL2)

set_target_properties(test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;$<TARGET_FILE_DIR:SDL2>;${ARM_OPENGLES_PATH}")