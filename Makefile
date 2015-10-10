
GCMODE := -DUSE_GC
GCLIBS := -lgc

CC := gcc
CFLAGS := -g -std=gnu99 -Wall -I./include $(GCMODE)
LIBS := -lbsd $(GCLIBS)

HDRS := $(wildcard include/*.h)
SRCS := $(wildcard src/*.c)
OBJS := $(shell echo "$(SRCS)" | perl -lpe "s/\bsrc/build/g; s/.c\b/.o/g")

build/pscm: $(OBJS)
	gcc -o build/pscm $(OBJS) $(LIBS)

build/%.o: src/%.c $(HDRS) Makefile
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf build
	mkdir build
	touch build/.keep
