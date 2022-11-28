#!/usr/bin/bash 

# Author: Chris Bao
# Generate one million seven digits random integers
# based on shuf utility

shuf -i 1000000-9999999 -n 7777777 > ./input.txt
