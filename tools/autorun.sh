#!/bin/bash

# This is the file that is run at startup on the Beagle board.

PROCFILE="/tmp/testcommit.txt"
REPODIR="/home/root/readonly-repo"

cd "$REPODIR"
while sleep 10; do
	# Certificate checking is broken in this wget version
	/home/root/wget --quiet --no-check-certificate \
			--post-data='beagleping=1' \
			-O "$PROCFILE" https://www.wijtemans.nl/IN4342.php

	if [ -s "$PROCFILE" ]
	then
		BRANCH=$(cat -- "$PROCFILE")
		git fetch
		git checkout "$BRANCH"
		git pull
		COMMIT=$(git rev-parse --short HEAD)

		export WORKDIR="/tmp/autotest"
		./compile_board.sh

		cd "$WORKDIR"
		EXECTIME=$(./run_board.sh)
		cd "$REPODIR"

		/home/root/wget --quiet --no-check-certificate \
				--post-data="beaglebranch=$BRANCH&beaglecommit=$COMMIT&beagleresult=$EXECTIME" \
				-O "$PROCFILE" https://www.wijtemans.nl/IN4342.php

	fi
done

