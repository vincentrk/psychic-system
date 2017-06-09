SHELL = /bin/sh

BASE_TOOLCHAIN := /opt/bbToolChain/usr/local/share/codesourcery/

CXX := arm-none-linux-gnueabi-g++

DSPLINK := /opt/bbToolChain/usr/local/share/bbframework/platform/beagle-linux/tools/dsplink_linux_1_65_00_03

#   ----------------------------------------------------------------------------
#   General options, sources and libraries
#   ----------------------------------------------------------------------------
CXXSRCS := main.cpp meanshift.cpp meanshift_portable.cpp pool_notify.cpp
OBJS :=
DEBUG :=
LDFLAGS := -lpthread -lm --sysroot=/opt/rootfs
CFLAGS := --sysroot=/opt/rootfs
LIBS := -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
BIN := meanshift.gpp

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags for Debug
#   ----------------------------------------------------------------------------
OBJDIR_DXX := Debug
BINDIR_D := $(OBJDIR_DXX)
LIBS_D := $(DSPLINK)/gpp/BUILD/EXPORT/DEBUG/dsplink.lib $(LIBS)
# If the DSP/Link was rebuilt by the user, replace the line above
# with the one below to use the updated libraries
#LIBS_D := $(DSPLINK)/gpp/BUILD/EXPORT/DEBUG/dsplink.lib $(LIBS)
OBJS_D := $(CXXSRCS:%.cpp=$(OBJDIR_DXX)/%.o)
ALL_DEBUG := -g -DDDSP_DEBUG $(DEBUG) -D__DEBUG -DDEBUG

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags for Release
#   ----------------------------------------------------------------------------
OBJDIR_RXX := Release
BINDIR_R := $(OBJDIR_RXX)
#LIBS_R := $(DSPLINK)/gpp/export/BIN/Linux/OMAPL1XX/RELEASE/dsplink.lib $(LIBS)
# If the DSP/Link was rebuilt by the user, replace the line above
# with the one below to use the updated libraries
LIBS_R := $(DSPLINK)/gpp/BUILD/EXPORT/RELEASE/dsplink.lib $(LIBS)
OBJS_R := $(CXXSRCS:%.cpp=$(OBJDIR_RXX)/%.o)

#   ----------------------------------------------------------------------------
#   Compiler include directories
#   ----------------------------------------------------------------------------
INCLUDES := -I$(DSPLINK)/gpp/inc                   \
            -I$(DSPLINK)/gpp/inc/usr               \
            -I$(DSPLINK)/gpp/inc/sys/Linux         \
            -I$(DSPLINK)/gpp/inc/sys/Linux/2.6.18  \
            -I$(BASE_TOOLCHAIN)/include \
            -I./

#   ----------------------------------------------------------------------------
#   All compiler options to be passed to the command line
#   ----------------------------------------------------------------------------
ALL_CFLAGS := $(INCLUDES)                   \
              -mlittle-endian               \
              -march=armv5t                 \
              -mtune=cortex-a8              \
              -Uarm                         \
              -marm -Wall                   \
              -Wno-trigraphs                \
              -fno-strict-aliasing          \
              -fno-common                   \
              -fomit-frame-pointer          \
              -mapcs                        \
              -c                            \
              -mabi=aapcs-linux             \
              -O3                           \
              -mfpu=neon                    \
              -mfloat-abi=softfp            \
              -ftree-vectorize              \
              -ffast-math                   \
              -funsafe-math-optimizations   \
              -funroll-loops                \
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
               -DDA8XXGEM_PHYINTERFACE=SHMEM_INTERFACE \
               -DARMCC               \
               -DOPTIMAL             \
               -DUSE_NEON            \
#               -DTIMEDETAIL          \
#               -DDSP_MIMIC           \
#               -DDSP                 \

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
	echo Compiling Debug...
	$(BASE_TOOLCHAIN)/bin/$(CXX) -o $@ $(OBJS_D) $(LIBS_D) $(LDFLAGS)

$(OBJDIR_DXX)/%.o : %.cpp
	$(BASE_TOOLCHAIN)/bin/$(CXX) $(ALL_DEBUG) $(DEFS) $(ALL_CFLAGS) -o$@ $<

#   ----------------------------------------------------------------------------
#   Building Release...
#   ----------------------------------------------------------------------------
.PHONY: Release
Release: $(BINDIR_R)/$(BIN)

$(BINDIR_R)/$(BIN): $(OBJS_R)
	echo Compiling Release...
	$(BASE_TOOLCHAIN)/bin/$(CXX) -o $@ $(OBJS_R) $(LIBS_R) $(LDFLAGS)

$(OBJDIR_RXX)/%.o : %.cpp
	$(BASE_TOOLCHAIN)/bin/$(CXX) $(DEFS) $(ALL_CFLAGS) -o$@ $<

.PHONY: clean
clean:
	@rm -f $(OBJDIR_DXX)/*
	@rm -f $(OBJDIR_RXX)/*
