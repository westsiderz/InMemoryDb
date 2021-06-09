#!/bin/sh

cmake -G "Eclipse CDT4 - Unix Makefiles" -S . -B build

cd build

make
