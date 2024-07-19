include config.mk

CC=cc

all: build/libsmdbottom.so.$(VERSION)

build/libsmdbottom.so.$(VERSION): $(OBJS)
	$(CC) $(OBJS) -shared -Wl,-soname,libsmdbottom.so -o $@

build/matches.o: src/matches.c
	$(CC) -fpic -o $@ -c $<

build/fullstrs.o: src/fullstrs.c
	$(CC) -fpic -o $@ -c $<

build/stdfds.o: src/stdfds.c
	$(CC) -fpic -o $@ -c $<

build/procaproc.o: src/procaproc.c
	$(CC) -fpic -o $@ -c $<

install: all
	sudo install build/libsmdbottom.so.$(VERSION) $(PREFIX)/lib/
	sudo ln -s  $(PREFIX)/lib/libsmdbottom.so.$(VERSION) $(PREFIX)/lib/libsmdbottom.so

clean:
	rm -f $(OBJS) build/libsmdbottom.so.$(VERSION)
	sudo rm -f $(PREFIX)/lib/libsmdbottom.so $(PREFIX)/lib/libsmdbottom.so.$(VERSION)
	sudo rm -rf $(PREFIX)/include/smdbottom
