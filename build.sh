#!/bin/bash

if [ -f "./main.cpp" ]; then
    echo "main.cpp found."
else
    echo "Cannot find main.cpp. Please change current working directory to the project root directory."
    exit
fi

files=(
    "main.cpp"                          # 0
    "powermgr/power.cpp"                # 1
)

echo "Files:"
echo "${files[@]}"

/usr/bin/g++ --version
/usr/bin/g++ "${files[@]}" \
             -O0 \
             -l "stdc++" \
             -l "ncurses" \
             -l "tinfo" \
             -Wall \
             -Wextra \
             -Wnull-dereference \
             -Wdangling-pointer \
             -std=c++23 \
             -static \
             --debug \
             --verbose