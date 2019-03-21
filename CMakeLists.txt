cmake_minimum_required(VERSION 3.12)

project(FakeProjectiveSpaces)

find_package(Eigen3 CONFIG REQUIRED)

file( GLOB __CC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )
add_executable( main_app ${__CC_SRC} )

target_include_directories( main_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries(main_app PRIVATE Eigen3::Eigen)

install(
    TARGETS main_app
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
)