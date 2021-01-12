#!/bin/bash

if [ -z "$1" ]; then
    echo -e "\nPlease call '$0 <file.cpp>' to run this command!\n"
    exit 1
fi

g++ -Wall -g $1 include/* -L /usr/local/lib/ -lglfw -lGLU -lGL -o builded
./builded
