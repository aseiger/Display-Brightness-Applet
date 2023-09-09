# gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC testplugin.c -o testplugin.so `pkg-config --libs lxpanel`

SHELL = /bin/sh
CC    = gcc
FLAGS        = -Wall `pkg-config --cflags gtk+-2.0 lxpanel` `pkg-config --libs lxpanel`
CFLAGS       = -shared -fPIC

TARGET  = DisplayBrightnessApplet.so
SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)
LIBRARIES = -lddcutil

PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

INSTALLDIR = /usr/lib/aarch64-linux-gnu/lxpanel/plugins

all: $(TARGET)

install:
	cp $(TARGET) $(INSTALLDIR)/$(TARGET)
	
clean:
	rm $(shell echo *.so) $(shell echo *.o)

$(TARGET):
	$(CC) $(FLAGS) $(CFLAGS) $(LIBRARIES) $(SOURCES) -o $(TARGET)
