#!/bin/bash


function usage() {
    echo "Usage: configure.sh <opencilk path>"
}


if [ "$#" -ne 1 ]; then
    usage
    exit 1
fi

OPENCILK_PATH="$1" \
    cmake -S. -Bbuild \
    --fresh \
    -DCMAKE_TOOLCHAIN_FILE=opencilk.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DBUILD_TESTING=ON
