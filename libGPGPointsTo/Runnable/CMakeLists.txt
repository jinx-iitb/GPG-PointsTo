cmake_minimum_required(VERSION 3.16)
set(LLVM_ROOT "" CACHE PATH "/usr/lib/llvm-10")
# if(NOT EXISTS ${LLVM_ROOT}/include/llvm)
#     message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is invalid path.")
# endif()
list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}/share/llvm/cmake")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
link_directories(${LLVM_LIBRARY_DIRS})
include_directories(${LLVM_INCLUDE_DIRS})

add_library(LLVMGPGImpl1 SHARED IMPORTED)
set_target_properties(LLVMGPGImpl1 PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libLLVMGPGImpl.so")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Pass)