cmake_minimum_required(VERSION 3.12)

project(FakeProjectiveSpaces)

set (CMAKE_CXX_STANDARD 17)
find_package(Eigen3 CONFIG REQUIRED)

file( GLOB __CC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )
add_library( libfkps ${__CC_SRC} )

target_include_directories( libfkps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries(libfkps PRIVATE Eigen3::Eigen)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)