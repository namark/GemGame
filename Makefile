SHELL	= /bin/sh
COMP	= g++
ARCH	= ar

FLAGS	= --std=c++11
LINK	= -lSDL_drawing -lSDL -lSDLmain

SRCDIR	= source
OUTDIR	= out
OUTDMMY	= $(OUTDIR)/.ignoreThis.dummy.out
PREFIX	= $(DESTDIR)/usr/local
BINDIR	= $(PREFIX)/bin
INCDIR	= $(PREFIX)/include/SDL_drawing
LIBDIR	= $(PREFIX)/lib

TARGET	= GemGame
SOURCES	= $(shell echo $(SRCDIR)/*.cpp)
HEADERS	= $(shell echo $(SRCDIR)/*.h)
OBJECTS	= $(patsubst $(SRCDIR)/%.cpp,$(OUTDIR)/%.o,$(SOURCES))
OUT		= $(OUTDIR)/$(TARGET)

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp $(OUTDMMY)
	$(COMP) -c $(FLAGS) -o $@ $<

$(OUT): $(OBJECTS)
	$(COMP) $(OBJECTS) -o $(OUT) $(FLAGS) $(LINK)

setup:

$(OUTDMMY):
	@echo Creating output directory
	mkdir -p $(OUTDIR)
	touch $@
	@echo This is a dummy file for Makefile to know that the out directory was created. It will be removed by distclean along with the directory. > $@

install: $(OUT)
	cp $(OUT) $(BINDIR)/$(TARGET)

uninstall:
	-rm $(BINDIR)/$(TARGET)

clean:
	-rm -f $(OBJECTS)
	-rm -f gmon.out

distclean: clean
	-rm -f $(OUT)
	-rm -f $(OUTDMMY)
	-rmdir $(OUTDIR)

.PHONY : install uninstall clean distclean
