## CentOS 7.2 CMake Cross Build VTK for Android Application
 
### 1、Install Android NDK

wget https://dl.google.com/android/repository/android-ndk-r17-beta2-linux-x86_64.zip

7za x android-ndk-r17-beta2-linux-x86_64.zip

设置环境变量：
```
Vim /etc/profile 

add  export NDK_ROOT=/home/ndk/android-ndk-r17-beta2

source /etc/profile
```
 
### 2、Install Tools and cmake

Install mesa and xt
```
yum install mesa-libGL-devel
yum install mesa-libGLU-devel
yum install libXt-devel
```

Install cmake
```
https://cmake.org/download/
download cmake-3.13.2-Linux-x86_64.sh
chmod 755 cmake-3.13.2-Linux-x86_64.sh
./cmake-3.13.2-Linux-x86_64.sh --skip-license --prefix=/usr/
```

### 3、 Download VTK Soure

```
wget https://www.vtk.org/files/release/8.1/VTK-8.1.2.tar.gz
tar zxvf VTK-8.1.2.tar.gz
```


### 4、Run Shell
```
cd VTK-8.1.2
mkdir build
cd build
cp  auto_build_clean.sh auto_build_android.sh  build
./auto_build_android.sh
```


### just wait

also, You can also use the compiled Android VTK library.
you can download vtk-android.tar.gz 
from https://github.com/panyingyun/vtkandroiddemo/releases/download/1.0/vtk-android.tar.gz.


