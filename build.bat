@echo off
mkdir cmake-build
cd cmake-build
cmake .. -G "Unix Makefiles"
make
copy .\StuInfo-Manager.exe .. /y
cd ..
rmdir /s /q cmake-build
