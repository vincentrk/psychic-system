#!/bin/bash

# This script will be run on the Beagle board to compile the program.
# This script should produce no files in the git project directory.

SERVERACCOUNT="in4342-11@ce-eslab.ewi.tudelft.nl"
UUID=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)

if [ -e "$WORKDIR" ]
then
	rm -r "$WORKDIR"
fi

mkdir "$WORKDIR"

UPFILE="$WORKDIR/up.tar.gz"
tar -czf "$UPFILE" "ESLab_Assign01_Group11/code/"*

cd "$WORKDIR"

SERVERDIR="tmp/$UUID"
# The installed version of scp does not work with public key authentication.
ssh "$SERVERACCOUNT" "mkdir -p '$SERVERDIR'"
cat "$UPFILE" | ssh "$SERVERACCOUNT" "cat > '$SERVERDIR/down.tar'"
ssh "$SERVERACCOUNT" "cd '$SERVERDIR'; tar -xzf down.tar; cd gpp; make board;"
ssh "$SERVERACCOUNT" "cat '$SERVERDIR/gpp/matMult.exe'" > "myprogram.exe"

chmod +x myprogram.exe

