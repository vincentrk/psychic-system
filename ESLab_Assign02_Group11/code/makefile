EXEC_GPP=gpp/Release/meanshift.gpp
EXEC_DSP=dsp/meanshift.dsp

all: gpp dsp

gpp:
	$(MAKE) -C gpp

dsp:
	$(MAKE) -C dsp

send: all
	scp $(EXEC_GPP) $(EXEC_DSP) beagle.wijtemans.nl:/tmp/

.PHONY: clean all send gpp dsp
clean:
	$(MAKE) -C dsp clean
	$(MAKE) -C gpp clean

