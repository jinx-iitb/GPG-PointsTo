# libGPGPointsTo

#### About

This software has been released as a part of an SERB project on precise and scalable program analysis. The project started late, funding was delayed signigicantly so this is not a complete work and is a snapshot of the work when the sponsored project ended. Subsequently work is being carried out separately.

#### Installation
- Create a build folder inside the current directory.
- Build the project using the command from build directory.

  ```
  cmake ..
  ```
- After building the project execute the following command to install the library.

  ```
  sudo make install
  ```
#### Using the library
- Add the library to your project using the following lines in Outermost CMakeLists.txt
```
add_library(LLVMGPGImpl SHARED IMPORTED)
set_target_properties(LLVMGPGImpl PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libLLVMGPGImpl.so")
```
- In the CMakeLists where executable is created. Add the following lines to CMakeLists.txt
```
add_executable(<Executable_name> <list_of_cpp_file_linked_to_the_executable>)
set_target_properties(<Executable_name> PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti -g"    
)
target_link_libraries(<Executable_name> PRIVATE LLVMGPGImpl LLVMSupport LLVMCore LLVMIRReader LLVMLinker LLVMBitWriter)
```
- To use the functions from the library and perform the Pointer Analysis.
```
#include "GPGPTAnalysis/Driver.h"
```
- Create an instance of this driver class.
```
Driver* exec = new Driver(argc, argv);
```
- Call the Functions on this object created. This would print the pointer-analysis result.
```
exec->performAnalysis();
```
