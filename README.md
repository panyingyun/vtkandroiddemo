## CentOS 7.2 CMake Cross Build VTK for Android Application

### VTK Android移植过程记录：

#### T1、github 建立新的repo用于记录该过程
	demo1
	
#### T2、CentOS下cmake编译可执行的demonative代码
	(1) CentOS install lastest cmake 
	
	https://cmake.org/download/
	
	download cmake-3.13.2-Linux-x86_64.sh
	```
	chmod 755 cmake-3.13.2-Linux-x86_64.sh
	./cmake-3.13.2-Linux-x86_64.sh --skip-license --prefix=/usr/
	```
	
	(2) 下载ndk
	
	wget https://dl.google.com/android/repository/android-ndk-r17-beta2-linux-x86_64.zip
	
	7za x android-ndk-r17-beta2-linux-x86_64.zip
	
	设置环境变量：
	
	Vim /etc/profile 
	
	在最后添加一行 export NDK_ROOT=/home/ndk/android-ndk-r17-beta2
	
	source /etc/profile  生效
	
	(3) 创建简单的交叉编译工程demonative
	
	创建 cmake1.cpp 
	
	请参考：https://github.com/panyingyun/vtkandroiddemo/tree/master/demo1native
	
	(4) 编译对应的so库
	cmake -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake  \
	-DANDROID_NDK=$NDK_ROOT -DANDROID_ABI="armeabi-v7a" \
	-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 \
	-DANDROID_NATIVE_API_LEVEL=16 \
	-DANDROID_STL="c++_static" \
	-DCMAKE_BUILD_TYPE="Release" \
	-DCMAKE_C_FLAGS="-fpic -fexceptions -frtti" \
	-DCMAKE_CXX_FLAGS="-fpic -fexceptions -frtti" ..
	
	参数说明请参考：
	https://developer.android.com/ndk/guides/cmake
	https://fucknmb.com/2017/06/27/cmake-%E4%BA%A4%E5%8F%89%E7%BC%96%E8%AF%91/
	https://github.com/Tencent/ncnn/wiki/cmake-%E6%89%93%E5%8C%85-android-sdk

		
#### T3、创建C++项目目录并且编译生成so
    demo1cpp
	
#### T4、项目引用这个so
	通过javah命令生成jni头文件
	添加javah到环境变量PAHT中:
	C:\Program Files\Android\Android Studio\jre\bin
	使用脚本
	generateJNI.bat 自动生成jni头文件，注意必须找到对应的classes目录，并且需要指定正确的类名
    demo1
	在工程中增加jniLib/armeabi-v7a目录，把对应的so拷贝到该目录中
	详细见：
	https://github.com/panyingyun/vtkandroiddemo/tree/master/demo1
	
	JNI请参考：
	https://www.jianshu.com/p/0f34c097028a
	https://www.jianshu.com/p/b71aeb4ed13d
	
	ConstraintLayout布局文件请参考：
	https://juejin.im/entry/5a0f93b4f265da432717ce87
	https://mp.weixin.qq.com/s/gGR2itbY7hh9fo61SxaMQQ
	
#### T5、项目编译为apk
    demo1
	编译为测试APK
	
#### T6、编译VTK为so
	
	yum install mesa-libGL-devel
	yum install mesa-libGLU-devel
	yum install libXt-devel
	
	cmake  -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake  \
	-DCMAKE_ANDROID_NDK=$NDK_ROOT \
	-DCMAKE_VERBOSE_MAKE=ON \
	-DCMAKE_SYSTEM_NAME=Android \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_CXX_FLAGS='-std=c++11 -fpic -fexceptions -frtti' \
	-DCMAKE_C_FLAGS='-fpic' \
	-DCMAKE_ANDROID_STL_TYPE='c++_static' \
	-DCMAKE_SYSTEM_VERSION=24 \
	-DVTK_ANDROID_BUILD=ON \
	-DANDROID_NATIVE_API_LEVEL=24 \
	-DOPENGL_ES_VERSION=3.0 ..

	cmake --build . 

	**注意：遇到 vtk error: 'round' is not a member of 'std' ，则将  "std::round" 直接修改为 "round" 即可继续编译**
	
	直接这样就可以了
	
	参考：
	https://github.com/panyingyun/vtkandroiddemo/tree/master/vtkandroid/auto_build_android.sh

	Android编译完成的测试APK: JavaVTK.apk
	https://github.com/panyingyun/vtkandroiddemo/blob/master/vtkandroid/JavaVTK.apk

#### T7、 Compiled Android VTK library

	also, You can also use the compiled Android VTK library.
	you can download vtk-android.tar.gz 
	from https://github.com/panyingyun/vtkandroiddemo/blob/master/vtkandroid/vtk-android.tar.gz
	
#### T8、创建JavaVTK2工程，引入java调用native形式的VTK Demo

    https://github.com/panyingyun/vtkandroiddemo/tree/master/JavaVTK2


#### T9、参考链接

	https://cmake.org/cmake/help/v3.7/manual/cmake-toolchains.7.html#cross-compiling-for-android
	https://cmake.org/cmake/help/v3.7/manual/cmake-toolchains.7.html#cross-compiling-for-android-with-a-standalone-toolchain

	
#### T10、注意 如果遇到下面的错误，请使用VTK8.2.0库进行编译，旧库存在opengles兼容性问题

	https://gitlab.kitware.com/vtk/vtk/issues/16913
	https://github.com/spherik/Android-vtk-skeleton/issues/1
	
	Crash log, Maybe glESv3 have not support glDrawBuffer, only support glDrawBuffers.
		Call some help from :
	
```
	--------- beginning of crash
	kitware.com.volumerender E/AndroidRuntime: FATAL EXCEPTION: GLThread 3658
    Process: kitware.com.volumerender, PID: 16404
    java.lang.UnsatisfiedLinkError: dlopen failed: cannot locate symbol "glDrawBuffer" \
		referenced by "/data/app/kitware.com.volumerender-lhp_zoAPmbgFkLST-3uj1A==/lib/arm/libVolumeRender.so"...
        at java.lang.Runtime.loadLibrary0(Runtime.java:1016)
        at java.lang.System.loadLibrary(System.java:1669)
        at kitware.com.volumerender.VolumeRenderLib.<clinit>(VolumeRenderLib.java:41)
        at kitware.com.volumerender.VolumeRenderLib.init(Native Method)
        at kitware.com.volumerender.VolumeRenderView$Renderer.onSurfaceChanged(VolumeRenderView.java:160)
        at android.opengl.GLSurfaceView$GLThread.guardedRun(GLSurfaceView.java:1555)
        at android.opengl.GLSurfaceView$GLThread.run(GLSurfaceView.java:1270)
```
