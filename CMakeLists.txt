cmake_minimum_required(VERSION 3.12)

project(FakeProjectiveSpaces)

set (CMAKE_CXX_STANDARD 17)

file( GLOB __CC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )
file( GLOB __CC_HDR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )
file( GLOB __C_HDR  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library( libfkps ${__CC_SRC} )

target_include_directories( libfkps PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_include_directories( libfkps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)