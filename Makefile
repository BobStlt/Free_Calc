CC=gcc
CFLAGS = -Wall
TARGET = fcalc

free_calc: fcalc.c
	$(CC) $(CFLAGS) fcalc.c -o fcalc

install: fcalc
	mv $(TARGET) /usr/bin/$(TARGET)

clean:
	$(RM) $(TARGET)
