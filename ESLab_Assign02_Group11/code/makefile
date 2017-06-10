GPP_DIR=gpp
DSP_DIR=dsp
EXEC_GPP=$(GPP_DIR)/Release/meanshift.gpp
EXEC_DSP=$(DSP_DIR)/Release/meanshift.dsp


.PHONY: all
all: neon


.PHONY: neon
neon:
	$(MAKE) -C $(GPP_DIR) neon


.PHONY: dsp
dsp: dspcode
	$(MAKE) -C $(GPP_DIR) dsp


.PHONY: fixedpoint
fixedpoint:
	$(MAKE) -C $(GPP_DIR) fixedpoint


.PHONY: floatingpoint
floatingpoint:
	$(MAKE) -C $(GPP_DIR) Release



.PHONY: dspcode
dspcode:
	$(MAKE) -C $(DSP_DIR)


.PHONY: send
send:
	-scp $(EXEC_GPP) $(EXEC_DSP) $(GPP_DIR)/run.sh beagle.wijtemans.nl:/tmp/
#	scp $(EXEC_GPP) $(GPP_DIR)/run.sh beagle.wijtemans.nl:/tmp/


.PHONY: clean
clean:
	$(MAKE) -C $(DSP_DIR) clean
	$(MAKE) -C $(GPP_DIR) clean

