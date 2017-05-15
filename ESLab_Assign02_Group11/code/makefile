GPP_DIR=gpp-for-dsp
DSP_DIR=dsp
EXEC_GPP=$(GPP_DIR)/Release/meanshift.gpp
EXEC_DSP=$(DSP_DIR)/Release/meanshift.dsp

all: gpp dsp

gpp:
	$(MAKE) -C $(GPP_DIR)

dsp:
	$(MAKE) -C $(DSP_DIR)

send: all
	scp $(EXEC_GPP) $(EXEC_DSP) $(GPP_DIR)/run.sh beagle.wijtemans.nl:/tmp/

.PHONY: clean all send gpp dsp
clean:
	$(MAKE) -C dsp clean
	$(MAKE) -C $(GPP_DIR) clean

