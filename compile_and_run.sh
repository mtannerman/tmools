#!/bin/bash

cd tests/build/
cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/clang++-6.0 ../../ || exit 1
make tmools_main || exit 1


./tmools_main