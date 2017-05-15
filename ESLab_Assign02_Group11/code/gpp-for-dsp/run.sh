#!/bin/bash
/home/root/powercycle.sh > /dev/null

MYDIR=$(pwd)
"$MYDIR/meanshift.gpp" /home/root/car.avi "$MYDIR/meanshift.dsp" 65536

/home/root/powercycle.sh > /dev/null

