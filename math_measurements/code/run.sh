#!/bin/bash

size=4
maxsize=$(( 1024 * 4 ))

while [ $size -le $maxsize ]
do
    ./main.gpp $size
    size=$(( $size + 4 ))
done

