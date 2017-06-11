IN4342 Assginment 02 Code
	GROUP 11-
		Aniket Dhar
		Anirudh Bisht
		Lars Wijtemans
		Philip Dürnay
		Sergio Soto
		Vincent Koeten

This code base contains 4 distinct versions of the Mean Shift Algorithm.
To choose which version is compile use the appropriate make targets.
Each version is further described in our report.
	'make floatingpoint'
		compiles our floating point version (ARM-Float).
	'make fixedpoint'
		compiles our fixed point version (ARM-Fixed).
	'make dsp'
		compiles our DSP version (DSP).
	'make neon'
		compiles our fastest and final solution (NEON).

	In addition there are several defines in the makefile under the gpp folder that add and remove functionality within the code.
		-DOPTIMAL Switch this flag out to enable extra error checking on the continuity of the kernel
		-DTIMEDETAIL Switch this flag in to enable extra timing analysis of the pdf representation function separately
