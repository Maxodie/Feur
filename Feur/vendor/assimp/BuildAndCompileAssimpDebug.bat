cmake -G "MinGW Makefiles" -DMAKE_C_COMPILER=C -DMAKE_CXX_COMPILER=CXX -DCMAKE_BUILD_TYPE=Debug -S./ -B./build

mingw32-make -C ./build

PAUSE