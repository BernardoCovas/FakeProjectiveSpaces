add_executable(fkps_app app_main.cc)
target_link_libraries(fkps_app libfkps)

install(
    TARGETS fkps_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)