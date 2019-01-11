#!/bin/bash
cmake -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake  \
-DANDROID_NDK=$NDK_ROOT -DANDROID_ABI="armeabi-v7a" \
-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 \
-DANDROID_NATIVE_API_LEVEL=16 \
-DANDROID_STL="c++_static" \
-DCMAKE_C_FLAGS="-fpic -fexceptions -frtti" \
-DCMAKE_CXX_FLAGS="-fpic -fexceptions -frtti" \
-DCMAKE_VERBOSE_MAKE=ON \
-DCMAKE_BUILD_TYPE=Release \
-DOPENGL_ES_VERSION=3.0 \
-DVTK_ANDROID_BUILD=ON \
-DANDROID_ARCH_ABI='armeabi-v7a' \
-DCMAKE_INSTALL_PREFIX='/home/ndk/androidvtk' ..

make -j8

