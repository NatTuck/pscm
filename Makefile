
CC := gcc
CFLAGS := -I./include

HDRS := $(wildcard include/*.h)
SRCS := $(wildcard src/*.c)
OBJS := $(shell echo "$(SRCS)" | perl -lpe "s/\bsrc/build/g; s/.c\b/.o/g")

build/pscm: $(OBJS)
	gcc -o build/pscm $(OBJS)

build/%.o: src/%.c $(HDRS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf build
	mkdir build
	touch build/.keep
