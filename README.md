An engine that uses LLVM/Clang to Jit C++
========================================================

The system uses clang to compile c++ to llvm bitcode. LLVM is used to load bitcode, get a pointer to an init function
in the bitcode module and execute the jit'd code. Ideally this will develop into a game engine runtime that can support
development of a game that does not need to be recompiled as a whole project.

Development Dependancies
========================
> all available in ubuntu repositories except for glfw3

llvm
boost filesystem
boost system
glfw3
glew
tinyxml2

clang is required to compile c or c++ modules to llvm bitcode. The command to do so is:
clang++ -c file.cpp -emit-llvm
to have clang output an IR file instead, this line works:
clang++ -S file.cpp -emit-llvm
