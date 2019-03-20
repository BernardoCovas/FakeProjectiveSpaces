cmake_minimum_required(VERSION 3.14)

file( GLOB __C_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc )

add_executable( partitionbatch ${__C_SRC} )
target_include_directories( partitionbatch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

install(
    TARGETS partitionbatch
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
)