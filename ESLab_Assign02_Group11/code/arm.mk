BASE_TOOLCHAIN=/opt/bbToolChain/usr/local/share/codesourcery
CC=$(BASE_TOOLCHAIN)/bin/arm-none-linux-gnueabi-g++

SRCS=meanshift.cpp main.cpp
OBJS=$(SRCS:%.cpp=%.o)
EXEC=meanshift.gpp

LDFLAGS=-lpthread -lm --sysroot=/opt/rootfs
LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video \
	-lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

DEFS=-DARMCC
#      -msoft-float

INCLUDES=-I. -I$(BASE_TOOLCHAIN)/include
CFLAGS=$(DEFS) $(INCLUDES)          \
	  -Wall -O3 -Wfatal-errors 		\
	  --sysroot=/opt/rootfs			\
      -mlittle-endian               \
      -march=armv5t                 \
			-funroll-loops								\
      -mtune=cortex-a8               \
      -Uarm                         \
      -marm                         \
			-mfpu=neon									\
			-mfloat-abi=softfp					\
			-ftree-vectorize						\
			-ffast-math									\
      -Wno-trigraphs                \
			-funsafe-math-optimizations			\
      -fno-strict-aliasing          \
      -fno-common                   \
      -fomit-frame-pointer       \
      -mapcs                        \

      -mabi=aapcs-linux

all: clean $(EXEC)


$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

send: $(EXEC)
	scp $(EXEC) beagle.wijtemans.nl:/tmp/

.PHONY: clean all send
clean:
	rm -f $(OBJS) $(EXEC) tracking_result.avi *~
