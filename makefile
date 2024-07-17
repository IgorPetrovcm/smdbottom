include config.mk

PREFIX=/usr/local

CC=cc

CFLAGS=-I ./include

OBJS=build/matches.o

HEADERS=include/matches.h

all: build/libsmdbottom.so.$(VERSION)

build/libsmdbottom.so.$(VERSION): $(OBJS)
	$(CC) $(OBJS) -shared -Wl,-soname,libsmdbottom.so.$(VERSION) -o $@

build/matches.o: src/matches.c include/matches.h
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

install: all
	sudo install build/libsmdbottom.so.$(VERSION) $(PREFIX)/lib/
	sudo ln -s  $(PREFIX)/lib/libsmdbottom.so.$(VERSION) $(PREFIX)/lib/libsmdbottom.so
	sudo mkdir $(PREFIX)/include/smdbottom/
	sudo install $(HEADERS) $(PREFIX)/include/smdbottom/ 

clean:
	rm -f $(OBJS) build/libsmdbottom.so.$(VERSION)
	sudo rm -f $(PREFIX)/lib/libsmdbottom.so $(PREFIX)/lib/libsmdbottom.so.$(VERSION)
	sudo rm -rf $(PREFIX)/include/smdbottom
