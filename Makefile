

build/gen/tokens.h build/gen/tokens.c: src/gen-tokenizer.rb
	echo ruby src/tokens/gen.rb $@



clean:
	rm -rf build
	mkdir build/gen
	touch build/gen/.keep
	mkdir build/bin
	touch build/bin/.keep
