@echo off
copy .\CMakeLists.txt .\CMakeLists.bak /y
echo SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK") >> CMakeLists.txt
mkdir cmake-build
cd cmake-build
cmake .. -G "Unix Makefiles"
make
copy .\StuInfo-Manager.exe .. /y
cd ..
rmdir /s /q cmake-build
copy .\CMakeLists.bak .\CMakeLists.txt /y
del .\CMakeLists.bak
