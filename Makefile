CC=gcc

free_calc: fcalc.c
	$(CC) fcalc.c -o fcalc

install: fcalc
	mv fcalc /usr/bin/fcalc

clean:
	rm fcalc
