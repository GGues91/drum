CC=gcc

#all: tre
#	make -C extension/ -f makefile

static:
	make -C extension/ -f makefile
	make tre

tre: main.o tokenizer.o retokenizer.o cutenizer.o miscellaneous.o token.o tok-dclr.o lorr.o wave.o extension/*.o
	$(CC) -lm -o $@ $^ &> cc.txt
#	$(CC) -lm -o $@ $^ extension/*.o &> cc.txt

%.o: %.c
	$(CC) -c $<

.PHONY: clean

clean:
	rm -f *.o tre
	make -C extension/ clean
