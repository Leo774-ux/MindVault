#!/bin/bash
set -e
mkdir -p build/linux && cd build/linux
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cp mindvault ../../bin/mindvault_linux_x86_64
echo "Linux build done: bin/mindvault_linux_x86_64"
