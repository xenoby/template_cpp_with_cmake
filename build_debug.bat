set PATH=%PATH%;C:\Program Files\CodeBlocks\MinGW\bin

cmake --preset mingw-debug
cmake --build --preset debug

start bin\w_app.exe
