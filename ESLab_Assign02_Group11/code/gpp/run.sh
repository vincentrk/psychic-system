#!/bin/bash

size=128
maxsize=129408
#$(( 1024 + 16))

MYDIR=$(pwd)

/home/root/powercycle.sh > /dev/null
while [ $size -le $maxsize ]
do
    "$MYDIR/meanshift.gpp" "$MYDIR/meanshift.dsp" $size
    size=$(( $size + 128 ))
done
/home/root/powercycle.sh > /dev/null

