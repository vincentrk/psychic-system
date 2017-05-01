CC=gcc
# Use the following (instead of gcc) for arm compiler on ES Lab Server
# CC=/opt/bbToolChain/usr/local/share/codesourcery/bin/arm-none-linux-gnueabi-gcc
CFLAGS= -O3 -Wall
LIBS= -lm
LDFLAGS=
EXEC = matMult
CSRCS = matrixmult.c Timer.c
OBJS = $(CSRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS)  -o $@ $? $(LIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	@-rm -rf $(EXEC) $(OBJS) *~

.PHONY: all run clean
