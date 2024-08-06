#!/bin/sh

echo "Cleaning debug build..."
cmake --build ./build/debug/ --target clean
echo "Cleaning release build..."
cmake --build ./build/release/ --target clean