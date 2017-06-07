#!/bin/bash

size=$(( 16 ))
maxsize=5392
#$(( 1024 + 16))

MYDIR=$(pwd)

/home/root/powercycle.sh > /dev/null
while [ $size -le $maxsize ]
do
    "$MYDIR/meanshift.gpp" "$MYDIR/meanshift.dsp" $size
    size=$(( $size + 32 ))
done
/home/root/powercycle.sh > /dev/null

