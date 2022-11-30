#!/bin/bash 
filename='output.txt'
prev=-1
sorted=1
while read line; do
    current=$((line + 0))
    if (( $prev > $current  ))
        then
            sorted=0
            break 
        else
            prev=$current
            continue 
    fi 
done < $filename


if (( $sorted > 0 )) 
    then 
        echo "File is sorted"
    else 
        echo "File is not sorted"

fi 

