set PATH=%PATH%;C:\Program Files\CodeBlocks\MinGW\bin

cmake --preset mingw-release
cmake --build --preset release

start bin\w_app.exe
