#!/bin/bash
/home/root/powercycle.sh > /dev/null

MYDIR=$(pwd)
"$MYDIR/meanshift.gpp" "$MYDIR/meanshift.dsp"

/home/root/powercycle.sh > /dev/null

