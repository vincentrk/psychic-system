#!/bin/bash


chmod +x ./gpp/Debug/helloDSPgpp

/home/root/powercycle.sh
./gpp/Release/pool_notify ./dsp/Release/pool_notify.out car.avi 2> /dev/null
#./gpp/Debug/pool_notify ./dsp/Debug/pool_notify.out car.avi 2> /dev/null

