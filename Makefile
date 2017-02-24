CC=gcc
CFLAGS = -Wall
TARGET = fcalc
TESTING = tfcalc

free_calc: fcalc.c
	$(CC) $(CFLAGS) fcalc.c -o fcalc

install: fcalc
	mv $(TARGET) /usr/bin/$(TARGET)

clean: fcalc
	$(RM) $(TARGET)
