#!/bin/bash

size=1
maxsize=$(( 1024 * 4 ))

while [ $size -le $maxsize ]
do
    ./main.gpp $size
    size=$(( $size + 1 ))
done

