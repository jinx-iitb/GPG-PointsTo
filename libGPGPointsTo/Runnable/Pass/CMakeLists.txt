cmake_minimum_required(VERSION 3.16)
project(GPGPointsTo2)
add_compile_definitions(VERBOSE_LEVEL=0)
add_compile_definitions(PRINT_TO_DOT=0)
add_compile_definitions(PRINT_STATS=1)

add_executable(GPGPointsTo main.cpp)
set_target_properties(GPGPointsTo PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti -g -fno-inline-functions"
)
# llvm_map_components_to_libnames(llvm_libs ${LLVM_TARGETS_TO_BUILD} all)
#llvm_map_components_to_libnames(llvm_libs_2 ${LLVM_TARGETS_TO_BUILD} support core irreader codegen mc mcparser option passes)
target_link_libraries(GPGPointsTo PUBLIC Spatial TransformIR LLVMGPGImpl1)
