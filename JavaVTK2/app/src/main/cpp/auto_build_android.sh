#!/bin/bash
rm -rf CMakeCache.txt
rm -rf CMakeFiles
rm -rf cmake_install.cmake
rm -rf Makefile
rm -rf CTestTestfile.cmake
rm -rf CMakeExternals  
rm -rf CMakeTmp  
rm -rf CompileTools  
rm -rf CTestCustom.cmake  
rm -rf ExternalData
rm -rf *.so

cmake .
cmake --build . --config Release

rm -rf CMakeCache.txt
rm -rf CMakeFiles
rm -rf cmake_install.cmake
rm -rf Makefile
rm -rf CTestTestfile.cmake
rm -rf CMakeExternals
rm -rf CMakeTmp
rm -rf CompileTools
rm -rf CTestCustom.cmake
rm -rf ExternalData
