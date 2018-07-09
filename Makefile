PROG = reverse
SRC = reverse.c
#CC=gcc

TOP = ./
CIVETWEB_LIB = libcivetweb.a
CIVETWEB_SRC = civetweb.c

CFLAGS = -I$(TOP)/include $(COPT)
LIBS = -lpthread

#include $(TOP)/resources/Makefile.in-os
TARGET_OS=LINUX

ifeq ($(TARGET_OS),LINUX)
	LIBS += -ldl
endif

all: $(PROG)

$(PROG): $(CIVETWEB_LIB) ./src/$(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) ./src/$(SRC) $(CIVETWEB_LIB) $(LIBS)

$(CIVETWEB_LIB): ./src/$(CIVETWEB_SRC)
	$(CC) -c -W -Wall -o2 -DLINUX $(CFLAGS) -DNDEBUG ./src/$(CIVETWEB_SRC) -o $@

clean:
	rm -f $(CIVETWEB_LIB) $(PROG)

.PHONY: all clean
