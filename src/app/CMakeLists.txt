add_executable(fkps_app app_main.cc)

target_link_libraries(fkps_app libfkps)
target_link_libraries(fkps_app stdc++fs)
target_link_libraries(fkps_app pthread)
target_link_libraries(fkps_app dl       )

install(
    TARGETS fkps_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)