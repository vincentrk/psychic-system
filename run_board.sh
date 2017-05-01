#!/bin/bash

# This script will be run on the Beagle board to test the program.
# It should produce a number representing the run time of the program.

./myprogram.exe | grep "Total Time = " |  awk '{print $4};'

