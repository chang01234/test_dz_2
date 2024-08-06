#!/bin/sh

if [ $# -ne 1 ]
then
    echo "You must have 1 and only 1 argument: release or debug"
elif [ "$1" = "release" ]
then
    echo "Creating Ninja Makefiles from CMake..."
    python3 ./tools/build/config-release.py

    echo "Pre Build steps..."
    python3 ./tools/build/pre-build.py

    echo "Building $1..."
    cmake --build ./build/release --config release --target all

    echo "Post Build steps..."
    python3 ./tools/build/post-build.py ./build/release /usr/local/mcuxpressoide/mcu_data .
elif [ "$1" = "debug" ]
then
    echo "Creating Ninja Makefiles from CMake..."
    python3 ./tools/build/config-debug.py

    echo "Pre Build steps..."
    python3 ./tools/build/pre-build.py

    echo "Building $1..."
    cmake --build ./build/debug --config debug --target all

    echo "Post Build steps..."
    python3 ./tools/build/post-build.py ./build/debug /usr/local/mcuxpressoide/mcu_data .
else
    echo "The build script can only take one of the following argument: release or debug."
fi