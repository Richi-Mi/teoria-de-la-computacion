#!/bin/bash
if [ -e "./build/main" ]; then
    rm "./build/main"
fi

gcc main.c ./libraries/*.c -o ./build/main
if [ -e "./build/main" ]; then
    ./build/main
fi
