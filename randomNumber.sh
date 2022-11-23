#!/usr/bin/bash 

# Author: Chris Bao
# Generate one million seven digits random integers
# based on shuf utility

shuf -i 1000000-9999999 -n 10000000 > ./input.txt
