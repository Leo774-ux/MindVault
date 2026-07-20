#!/bin/bash
set -e
mkdir -p build/win && cd build/win
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain_mingw.cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cp mindvault.exe ../../bin/mindvault_windows.exe
echo "Windows build done: bin/mindvault_windows.exe"
