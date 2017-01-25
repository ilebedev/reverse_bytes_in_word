all: reverse_bytes_in_word

reverse_bytes_in_word: reverse_bytes_in_word.c
	gcc -o reverse_bytes_in_word -O3 reverse_bytes_in_word.c

install: reverse_bytes_in_word
	cp $< $(DESTDIR)$(PREFIX)/usr/bin/reverse_bytes_in_word

clean:
	rm reverse_bytes_in_word
