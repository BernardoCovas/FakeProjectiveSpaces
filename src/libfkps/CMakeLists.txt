file(GLOB LIBFKPS_CC_SRCS *.cc)

file(GLOB LIBFKPS_CU_SRCS cuda/*.cu)
file(GLOB LIBFKPS_CU_CC_SRCS cuda/*.cc)


if(FKPS_CUDA_SUPPORT)
	add_definitions(-DLIBFKPS_USE_CUDA)
	list(APPEND LIBFKPS_CC_SRCS ${LIBFKPS_CU_SRCS})

	message("LibFkps sources: ${LIBFKPS_CC_SRCS}")
	add_library(libfkps ${LIBFKPS_CC_SRCS})

	find_package(CUDA)
	find_library(CUDA_NVRTC_LIB libnvrtc nvrtc HINTS "${CUDA_TOOLKIT_ROOT_DIR}/lib64" "${LIBNVRTC_LIBRARY_DIR}" "${CUDA_TOOLKIT_ROOT_DIR}/lib/x64" "/usr/lib64" "/usr/local/cuda/lib64")

	target_include_directories(libfkps PUBLIC ${CUDA_INCLUDE_DIRS})
	target_link_libraries(libfkps ${CUDA_NVRTC_LIB})
else()
	list(APPEND LIBFKPS_CC_SRCS ${LIBFKPS_CU_CC_SRCS})

	message("LibFkps sources: ${LIBFKPS_CC_SRCS}")
	add_library(libfkps ${LIBFKPS_CC_SRCS})
endif(FKPS_CUDA_SUPPORT)

if (WIN32)
  find_package(dlfcn-win32 REQUIRED)
  target_link_libraries(libfkps PRIVATE dlfcn-win32::dl)
endif () 
