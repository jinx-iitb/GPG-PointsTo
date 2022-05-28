set(LLVM_LINK_COMPONENTS support core irreader passes)
include_directories(./include)
include_directories(/usr/local/include/spatial)
include_directories(/usr/local/include/slim)
add_compile_definitions(VERBOSE_LEVEL=10)
add_compile_definitions(PRINT_TO_DOT=1)

add_library(LLVMGPGImpl SHARED
    src/FunctionWithGPG.cpp
    src/Driver.cpp
    src/IndirectionList.cpp
    src/Util.cpp
    src/GPG.cpp
    src/GPB.cpp
    src/GPU.cpp src/Partition.cpp
    src/TestCase.cpp
    src/UpdatedCoalescing.cpp
)

target_link_libraries(LLVMGPGImpl PUBLIC TransformIR Spatial)

set_target_properties(LLVMGPGImpl PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti -g -fno-inline-functions"
)

llvm_config (LLVMGPGImpl ${LLVM_LINK_COMPONENTS})


include(GNUInstallDirs)
install(TARGETS LLVMGPGImpl LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY
./include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
