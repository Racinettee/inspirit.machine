inspirit.machine
================

An engine that uses LLVM/Clang to Jit C++
========================================================

The system uses clang to compile c++ to llvm bitcode. LLVM is used to load bitcode, get a pointer to an init function
in the bitcode module and execute the jit'd code. Ideally this will develop into a game engine runtime that can support
development of a game that does not need to be recompiled as a whole project.
