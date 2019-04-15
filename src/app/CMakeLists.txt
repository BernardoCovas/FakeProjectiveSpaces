file(GLOB APP_CC_SRCS *.cc)
message("App CC sources: ${APP_CC_SRCS}")

add_executable(app_main ${APP_CC_SRCS})
target_link_libraries(app_main libfkps)