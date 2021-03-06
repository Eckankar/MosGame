# Makefile for MosGame

MOSMLC?=mosmlc
CC?=gcc
DYNLD?=ld -shared

MOSMLINCLUDES=/usr/include/mosml
MOSMLLIB=/usr/lib/mosml
NORMALLIB=/usr/lib

SDLLIBS=`sdl-config --libs`
SDLGFXLIBS=-lSDL_gfx
SDLIMAGELIBS=-lSDL_image

OPTS=-fno-defer-pop -fPIC -fno-stack-protector
SDLFLAGS=`sdl-config --cflags`
CFLAGS=-Dunix -O2 $(OPTS) -I$(MOSMLINCLUDES) $(SDLFLAGS) -std=c99
DYNLDLIBS=$(SDLLIBS) $(SDLGFXLIBS) $(SDLIMAGELIBS)

CFILES=display draw mosgame util event image surface
COBJS=$(foreach f, $(CFILES), obj/$f.o)


all: libmosgame.so MosGame.ui MosGame.uo

libmosgame.so: $(COBJS)
	$(DYNLD) -o libmosgame.so $(COBJS) $(DYNLDLIBS)

obj/%.o: C/%.c C/%.h C/general.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -I./C $< 

MosGame.uo MosGame.ui: SML/*.sig SML/*.sml SML/MosGame.mlp
	$(CC) -E -P -x c SML/MosGame.mlp -o MosGame.sml
	$(MOSMLC) -liberal -c -P full Dynlib.ui -toplevel MosGame.sml
	rm MosGame.sml

clean:
	rm -f obj/*.o
	rm -f *.so
	rm -f MosGame.sml MosGame.ui MosGame.uo
	rm -f examples/loadsave/test.bmp

test: all
	mosml -P full test.sml

install: all
	install -t $(MOSMLLIB) MosGame.ui MosGame.uo
	install -t $(NORMALLIB) libmosgame.so  

install-sym: all
	ln -fst $(NORMALLIB) $(CURDIR)/libmosgame.so
	ln -fst $(MOSMLLIB) $(CURDIR)/MosGame.ui $(CURDIR)/MosGame.uo
