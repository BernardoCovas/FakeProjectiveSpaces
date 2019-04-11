cmake_minimum_required(VERSION 3.10)

project(FakeProjectiveSpaces LANGUAGES CXX CUDA)

set (CMAKE_CXX_STANDARD 17)

option(CUDA_SUPPORT "Compile with cuda support" OFF)

file( GLOB __CC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )
file( GLOB __CC_HDR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh )
file( GLOB __C_HDR  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library( libfkps ${__CC_SRC} )


if (WIN32)
  find_package(dlfcn-win32 REQUIRED)
  target_link_libraries(libfkps PRIVATE dlfcn-win32::dl)
endif () 

target_include_directories( libfkps PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_include_directories( libfkps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )

# MAIN_APP

file(GLOB __CC_APP_SRCS   "${CMAKE_CURRENT_SOURCE_DIR}/src/app/commands/*.cc")
file(GLOB __CUDA_APP_SRC  "${CMAKE_CURRENT_SOURCE_DIR}/src/app/cuda/*.cc")

if(CUDA_SUPPORT)
	add_executable(fkps_app src/app/app_main.cc ${__CUDA_APP_SRC})
	set_target_properties( fkps_app PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
else()
	add_executable(fkps_app src/app/app_main.cc ${__CC_APP_SRCS})
endif(CUDA_SUPPORT)


target_link_libraries(fkps_app libfkps)
target_include_directories( fkps_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/app )
target_include_directories( fkps_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ )

if(CUDA_SUPPORT)
	message("Compiling with cuda support.")
	find_package(CUDA REQUIRED)
	target_include_directories( fkps_app PRIVATE ${CUDA_INCLUDE_DIRS} )
endif(CUDA_SUPPORT)

if (UNIX)
    target_link_libraries(fkps_app stdc++fs )
    target_link_libraries(fkps_app pthread  )
    target_link_libraries(fkps_app dl       )
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} setargv.obj")
endif(UNIX)

install(
    TARGETS fkps_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)