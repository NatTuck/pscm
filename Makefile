
CC := gcc -std=gnu11
CFLAGS := -g -Wall -I./include
LIBS := -lbsd -lreadline -lgc

GSRC := src/gen/types.c src/gen/prelude.c
GHDR := include/gen/types.h src/gen/prelude.h

HDRS := $(wildcard include/*.h) $(GHDR)
SRCS := $(wildcard src/*.c) $(GSRC)
OBJS := $(shell echo "$(SRCS)" | perl -lpe "s/\.c\b/.o/g")

bin/pscm: $(OBJS)
	$(CC) -o bin/pscm $(OBJS) $(LIBS)

src/%.o: src/%.c bin/.hdrs
	$(CC) -c -o $@ $< $(CFLAGS)

bin/.hdrs: $(HDRS) gencode Makefile
	touch bin/.hdrs

$(GSRC) $(GHDR): gencode

gencode: $(wildcard scripts/types/*.rb scripts/*.rb)
	(cd scripts && ruby ./gen-types.rb)
	(cd scripts && ruby ./gen-prelude.rb)

clean:
	rm -f $(OBJS)
	#
	rm -rf include/gen
	mkdir include/gen
	touch include/gen/.keep
	#
	rm -rf src/gen
	mkdir src/gen
	touch src/gen/.keep
	#
	rm -rf bin
	mkdir bin
	touch bin/.keep

prereqs:
	sudo apt-get install libbsd-dev libgc-dev

.PHONY: clean types prereqs
