# Makefile for MLDraw

MOSMLC=mosmlc
MOSMLINCLUDES=/home/sebbe/build/mosml/include
MOSMLLIB=/usr/lib/mosml
NORMALLIB=/usr/lib

OPTS=-fno-defer-pop
SDLFLAGS=`sdl-config --cflags`
CFLAGS=-Dunix -O2 $(OPTS) -I$(MOSMLINCLUDES) $(SDLFLAGS)

SDLGFXLIBS=-lSDL_gfx
SDLLIBS=`sdl-config --libs`

CC=gcc
DYNLD=ld -shared $(SDLLIBS) $(SDLGFXLIBS)

CFILES=display draw mosgame util event
COBJS=$(foreach f, $(CFILES), obj/$f.o)


all: libmosgame.so MosGame.ui MosGame.uo

libmosgame.so: $(COBJS)
	$(DYNLD) -o libmosgame.so $(COBJS)

obj/%.o: C/%.c C/%.h C/general.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -I./C $< 

MosGame.uo MosGame.ui: SML/*.sig SML/*.sml SML/MosGame.mlp
	$(CC) -E -P -x c SML/MosGame.mlp -o MosGame.sml
	$(MOSMLC) -c -P full Dynlib.ui -toplevel MosGame.sml
	rm MosGame.sml

clean:
	rm -f obj/*.o
	rm -f *.so
	rm -f MosGame.sml MosGame.ui MosGame.uo

test: all
	mosml -P full test.sml

install: all
	install -t $(MOSMLLIB) MosGame.ui MosGame.uo
	install -t $(NORMALLIB) libmosgame.so  

install-sym: all
	ln -fst $(NORMALLIB) $(CURDIR)/libmosgame.so
	ln -fst $(MOSMLLIB) $(CURDIR)/MosGame.ui $(CURDIR)/MosGame.uo
