cmake -G "Visual Studio 15 2017 Win64"  -DUSE_SQRT=OFF  ..
cmake --build . --config Release
cd Release
cmake2.exe  16  9
cmake2.exe  1  25
cmake2.exe  1  9
cmake2.exe  2  2
cmake2.exe  3  3
pause