cmake_minimum_required (VERSION 3.8)

project ("FakeProjectiveSpaces" LANGUAGES C CXX CUDA)
set (CMAKE_CXX_STANDARD 17)

option(FKPS_CUDA_SUPPORT "Compile with cuda support" ON)

add_subdirectory("./src/libfkps")
add_subdirectory("./src/app")

target_include_directories(libfkps  PUBLIC "./include")
target_include_directories(app_main PUBLIC "./include")