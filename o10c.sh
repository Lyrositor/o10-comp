#!/usr/bin/env bash
# Usage: ./o10c input_file output_file

PATH=$(pwd):build:$PATH
o10c -co --output=/tmp/o10c.comp.asm $1
gcc -ggdb -x assembler -s /tmp/o10c.comp.asm -o $2
