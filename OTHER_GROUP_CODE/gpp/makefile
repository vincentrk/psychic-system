SHELL = /bin/sh

BASE_TOOLCHAIN := /opt/bbToolChain/usr/local/share/codesourcery/

CC := arm-none-linux-gnueabi-gcc
CCP := arm-none-linux-gnueabi-g++

DSPLINK := /opt/bbToolChain/usr/local/share/bbframework/platform/beagle-linux/tools/dsplink_linux_1_65_00_03

#   ----------------------------------------------------------------------------
#   General options, sources and libraries
#   ----------------------------------------------------------------------------
SRCS := pool_notify.c
SRCSCPP := gpp_main.cpp meanshift.cpp
OBJS :=
DEBUG :=
DEFS=-DARMCC
LDFLAGS := -lpthread -lm --sysroot=/opt/rootfs
CFLAGS := -DDSP
LIBS :=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video \
    -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
BIN := optimized-tracking

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags for Debug
#   ----------------------------------------------------------------------------
OBJDIR_D := Debug
BINDIR_D := $(OBJDIR_D)
LIBS_D := $(DSPLINK)/gpp/BUILD/EXPORT/RELEASE/dsplink.lib $(LIBS)
# If the DSP/Link was rebuilt by the user, replace the line above 
# with the one below to use the updated libraries
#LIBS_D := $(DSPLINK)/gpp/BUILD/EXPORT/DEBUG/dsplink.lib $(LIBS)
OBJS_D := $(SRCS:%.c=$(OBJDIR_D)/%.o)
OBJS_D += $(SRCSCPP:%.cpp=$(OBJDIR_D)/%.o)
ALL_DEBUG := -g -DDDSP_DEBUG $(DEBUG) -D__DEBUG -DDEBUG

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags for Release
#   ----------------------------------------------------------------------------
OBJDIR_R := Release
BINDIR_R := $(OBJDIR_R)
#LIBS_R := $(DSPLINK)/gpp/export/BIN/Linux/OMAPL1XX/RELEASE/dsplink.lib $(LIBS)
# If the DSP/Link was rebuilt by the user, replace the line above 
# with the one below to use the updated libraries
LIBS_R := $(DSPLINK)/gpp/BUILD/EXPORT/RELEASE/dsplink.lib $(LIBS)
OBJS_R := $(SRCS:%.c=$(OBJDIR_R)/%.o)
OBJS_R += $(SRCSCPP:%.cpp=$(OBJDIR_R)/%.o)

#   ----------------------------------------------------------------------------
#   Compiler include directories 
#   ----------------------------------------------------------------------------
INCLUDES := -I$(DSPLINK)/gpp/inc                   \
            -I$(DSPLINK)/gpp/inc/usr               \
            -I$(DSPLINK)/gpp/inc/sys/Linux         \
            -I$(DSPLINK)/gpp/inc/sys/Linux/2.6.18  \
            -I$(BASE_TOOLCHAIN)/include 	\
	    -I../common				\
	    -I../				\
            -I./

#   ----------------------------------------------------------------------------
#   All compiler options to be passed to the command line
#   ----------------------------------------------------------------------------
ALL_CFLAGS := $(INCLUDES)			\
	    -Wall -O3 -Wfatal-errors		\
    	    --sysroot=/opt/rootfs		\
    	    -mlittle-endian			\
    	    -march=armv7-a			\
    	    -mtune=cortex-a8			\
    	    -ftree-vectorize			\
    	    -mfloat-abi=softfp			\
    	    -mfpu=neon				\
    	    -ffast-math				\
    	    -Uarm				\
    	    -marm				\
    	    -Wno-trigraphs			\
    	    -fno-common				\
    	    -fno-omit-frame-pointer		\
    	    -mapcs				\
	    -mlittle-endian               	\
    	    -mabi=aapcs-linux			\
	    -c					\
	    $(CFLAGS)

#   ----------------------------------------------------------------------------
#   Compiler symbol definitions 
#   ----------------------------------------------------------------------------

DEFS :=        -DOS_LINUX            \
               -DMAX_DSPS=1          \
               -DMAX_PROCESSORS=2    \
               -DID_GPP=1            \
               -DOMAPL1XX            \
               -DPROC_COMPONENT      \
               -DPOOL_COMPONENT      \
               -DNOTIFY_COMPONENT    \
               -DMPCS_COMPONENT      \
               -DRINGIO_COMPONENT    \
               -DMPLIST_COMPONENT    \
               -DMSGQ_COMPONENT      \
               -DMSGQ_ZCPY_LINK      \
               -DCHNL_COMPONENT      \
               -DCHNL_ZCPY_LINK      \
               -DZCPY_LINK           \
               -DKFILE_DEFAULT       \
               -DDA8XXGEM            \
               -DDA8XXGEM_PHYINTERFACE=SHMEM_INTERFACE

#   ----------------------------------------------------------------------------
#   Compiler and Linker procedure
#   From this point and on changes are very unlikely.
#   ----------------------------------------------------------------------------
.PHONY: all
all: Debug Release

#   ----------------------------------------------------------------------------
#   Building Debug... 
#   ----------------------------------------------------------------------------
.PHONY: Debug
Debug: $(BINDIR_D)/$(BIN)

$(BINDIR_D)/$(BIN): $(OBJS_D)
	@echo Compiling Debug...
	@echo $(OBJS_D)
	$(BASE_TOOLCHAIN)/bin/$(CCP) -o $@ $(OBJS_D) $(LIBS_D) $(LDFLAGS)

$(OBJDIR_D)/%.o : %.c
	@$(BASE_TOOLCHAIN)/bin/$(CC) $(ALL_DEBUG) $(DEFS) $(ALL_CFLAGS) -o$@ $<

$(OBJDIR_D)/%.o : %.cpp
	@$(BASE_TOOLCHAIN)/bin/$(CCP) $(ALL_DEBUG) $(DEFS) $(ALL_CFLAGS) -Wno-write-strings -o$@ $<

#   ----------------------------------------------------------------------------
#   Building Release... 
#   ----------------------------------------------------------------------------
.PHONY: Release
Release: $(BINDIR_R)/$(BIN)

$(BINDIR_R)/$(BIN): $(OBJS_R)
	@echo Compiling Release...
	@$(BASE_TOOLCHAIN)/bin/$(CC) -o $@ $(OBJS_R) $(LIBS_R) $(LDFLAGS)

$(OBJDIR_R)/%.o : %.c
	@$(BASE_TOOLCHAIN)/bin/$(CC) $(DEFS) $(ALL_CFLAGS) -o$@ $<

$(OBJDIR_R)/%.o : %.cpp
	@$(BASE_TOOLCHAIN)/bin/$(CCP) $(DEFS) $(ALL_CFLAGS) -Wno-write-strings -o$@ $<

.PHONY: clean
clean:
	@rm -f $(OBJDIR_D)/*
	@rm -f $(OBJDIR_R)/* *~

