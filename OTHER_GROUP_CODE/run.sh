#!/bin/bash

EXEC_GPP="./gpp/Release/optimized-tracking"
EXEC_DSP="./dsp/Release/dsp-optimized-tracking.out"
CMD="$EXEC_GPP $EXEC_DSP car.avi"

/home/root/powercycle.sh

## Normal execution (errors are piped to /dev/null to remove clutter from opencv
## due to the lack of hardware acceleration).
./$CMD 2> /dev/null

## Run GPROF on the executable
#gprof -b $EXEC_GPP > gprof.txt

## Run Callgrind on the application
#export VALGRIND_LIB=/home/root/valgrind/.in_place
#export PATH="$PATH:/home/root/valgrind"
#~/nstrip/patchelf-0.9/src/patchelf --set-interpreter ~/nstrip/libc/ld-linux.so.3 $EXEC_GPP
#valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./$CMD

