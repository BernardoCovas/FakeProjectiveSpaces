add_executable(fkps_app app_main.cc)

target_link_libraries(fkps_app libfkps  )

if (UNIX)
    target_link_libraries(fkps_app stdc++fs )
    target_link_libraries(fkps_app pthread  )
    target_link_libraries(fkps_app dl       )
endif (UNIX)

install(
    TARGETS fkps_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)