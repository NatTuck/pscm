
#GCMODE := 
#GCLIBS := -lgc

GCMODE := -DREFCOUNT
GCLIBS := 

CC := gcc -std=gnu11
CFLAGS := -g -Wall -I./include $(GCMODE)
LIBS := -lbsd $(GCLIBS)

HDRS := $(wildcard include/*.h)
SRCS := $(wildcard src/*.c)
OBJS := $(shell echo "$(SRCS)" | perl -lpe "s/\bsrc/build/g; s/.c\b/.o/g")

build/pscm: $(OBJS) build/gen-types.o
	$(CC) -o build/pscm $(OBJS) build/gen-types.o $(LIBS)

build/%.o: src/%.c build/hdrs
	$(CC) -c -o $@ $< $(CFLAGS)

build/hdrs: $(HDRS) types Makefile
	touch build/hdrs

build/gen-types.o: types
	$(CC) -c -o $@ src/gen/types.c $(CFLAGS)

types: $(wildcard scripts/types/*.rb scripts/*.rb)
	(cd scripts && ruby ./gen-types.rb)

clean:
	rm -rf include/gen
	mkdir include/gen
	touch include/gen/.keep
	#
	rm -rf src/gen
	mkdir src/gen
	touch src/gen/.keep
	#
	rm -rf build
	mkdir build
	touch build/.keep

.PHONY: clean types
