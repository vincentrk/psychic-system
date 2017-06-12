This project tree is the deliverable of Group 3 for the course IN4342.

Contributors:
    Thijmen Ketel
    Vito Kortbeek
    Jeroen Overman
    Lourens Pool
    Bram Renting

The code for the DSP is located in the dsp folder
The code for the GPP is located in the gpp folder

There is a top level makefile which calls the makefile of both the GPP and DSP
if fine grained controll over the makefile variables is needed one should call
the makefile for both the GPP and DSP directly.

The run.sh script contains the commands needed to run the program on the GPP.

The folder common contains shared memory defenitions.

The file config.h includes the current configuration of the project.
    To run the algorithm on the GPP only, callshift on the DSP Only or
    callshift partially on the GPP and partially on the GPP one should change
    
    The default is to run only on the GPP.
