#!/usr/bin/env bash
# Usage: ./o10c input_file output_file

./o10c -co --output=/tmp/o10c.comp.asm $1
gcc -x assembler -s /tmp/o10c.comp.asm -o $2
