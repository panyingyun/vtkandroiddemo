#!/bin/bash
rm -rf CMakeCache.txt
rm -rf CMakeFiles
rm -rf cmake_install.cmake
rm -rf Makefile
rm -rf CTestTestfile.cmake

cmake -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake  \
-DANDROID_NDK=$NDK_ROOT -DANDROID_ABI="armeabi-v7a" \
-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 \
-DANDROID_NATIVE_API_LEVEL=16 \
-DANDROID_STL="c++_static" \
-DCMAKE_C_FLAGS="-fpic -fexceptions -frtti" \
-DCMAKE_CXX_FLAGS="-fpic -fexceptions -frtti" ..

make
