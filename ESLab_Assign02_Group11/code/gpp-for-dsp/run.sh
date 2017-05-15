#!/bin/bash
/home/root/powercycle.sh > /dev/null

MYDIR=$(pwd)
"$MYDIR/meanshift.gpp" "$MYDIR/meanshift.dsp" 1024

/home/root/powercycle.sh > /dev/null

