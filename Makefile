
GCMODE := -DUSE_GC
GCLIBS := -lgc

CXX := g++ -std=gnu++11
CFLAGS := -g -Wall -I./include $(GCMODE)
LIBS := -lbsd $(GCLIBS)

HDRS := $(wildcard include/*.hh)
SRCS := $(wildcard src/*.cc)
OBJS := $(shell echo "$(SRCS)" | perl -lpe "s/\bsrc/build/g; s/.cc\b/.o/g")

build/pscm: $(OBJS)
	$(CXX) -o build/pscm $(OBJS) $(LIBS)

build/%.o: src/%.cc $(HDRS) Makefile
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf build
	mkdir build
	touch build/.keep
