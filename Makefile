CC= gcc
CFLAGS= -Wall
CFILES= main.c calcFunctions.c inputOutput.c SingleLinkedList.c
TESTCFILES= calcFunctionsTest.c  SingleLinkedListTest.c  stackTest.c 
HFILES= calcFunctions.h inputOutput.h SingleLinkedList.h SingleLinkedList.h
OFILES= $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/inputOutput.o $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o

BUILDDIR=Build
TCODEDIR=TestCode
INSTDIR= /usr/bin
EXE= $(BUILDDIR)/calcFunctionsTest $(BUILDDIR)/SingleLinkedListTest $(BUILDDIR)/stackTest $(BUILDDIR)/fcalc $(BUILDDIR)/prototype
ALLOFILES= $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/inputOutput.o $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o $(BUILDDIR)/calcFunctionsTest.o $(BUILDDIR)/SingleLinkedListTest.o $(BUILDDIR)/stackTest.o $(BUILDDIR)/prototype.o $(BUILDDIR)/main.o

#Here is the main build
$(BUILDDIR)/fcalc : $(BUILDDIR)/main.o $(OFILES) $(CFILES) $(HFILES)
	$(CC) $(BUILDDIR)/main.o $(OFILES) $(CFLAGS) -o $(BUILDDIR)/fcalc

$(BUILDDIR)/main.o : $(OFILES) main.c
	$(CC) -c main.c $(CFLAGS) -o $(BUILDDIR)/main.o

$(BUILDDIR)/calcFunctions.o : calcFunctions.c calcFunctions.h $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o
	$(CC) -c calcFunctions.c $(CFLAGS) -o $(BUILDDIR)/calcFunctions.o

$(BUILDDIR)/inputOutput.o : inputOutput.c inputOutput.h
	$(CC) -c inputOutput.c $(CFLAGS) -o $(BUILDDIR)/inputOutput.o

$(BUILDDIR)/stack.o: stack.c stack.h $(BUILDDIR)/SingleLinkedList.o SingleLinkedList.h
	$(CC) -c stack.c $(CFLAGS) -o $(BUILDDIR)/stack.o

$(BUILDDIR)/SingleLinkedList.o : SingleLinkedList.h SingleLinkedList.c
	$(CC) -c SingleLinkedList.c $(CFLAGS) -o $(BUILDDIR)/SingleLinkedList.o

#Here are the test programs
test : CFLAGS += -g -pg -static-libgcc -D test
test : $(BUILDDIR)/calcFunctionsTest $(BUILDDIR)/SingleLinkedListTest $(BUILDDIR)/stackTest $(BUILDDIR)/prototype $(BUILDDIR)/fcalc

$(BUILDDIR)/prototype: $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/stack.o $(BUILDDIR)/SingleLinkedList.o
	$(CC) prototype.c $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/stack.o $(BUILDDIR)/SingleLinkedList.o $(CFLAGS) -o $(BUILDDIR)/prototype

$(BUILDDIR)/calcFunctionsTest: $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/calcFunctionsTest.o $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o
	$(CC) $(BUILDDIR)/calcFunctionsTest.o $(BUILDDIR)/calcFunctions.o $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o $(CFLAGS) -o $(BUILDDIR)/calcFunctionsTest

$(BUILDDIR)/calcFunctionsTest.o: $(BUILDDIR)/calcFunctions.o $(TCODEDIR)/calcFunctionsTest.c $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o
	$(CC) -c $(TCODEDIR)/calcFunctionsTest.c $(CFLAGS) -o $(BUILDDIR)/calcFunctionsTest.o

$(BUILDDIR)/SingleLinkedListTest: $(BUILDDIR)/SingleLinkedListTest.o $(BUILDDIR)/SingleLinkedList.o
	$(CC) $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/SingleLinkedListTest.o $(CFLAGS) -o $(BUILDDIR)/SingleLinkedListTest

$(BUILDDIR)/SingleLinkedListTest.o: $(BUILDDIR)/SingleLinkedList.o $(TCODEDIR)/SingleLinkedListTest.c
	$(CC) -c $(TCODEDIR)/SingleLinkedListTest.c $(CFLAGS) -o $(BUILDDIR)/SingleLinkedListTest.o

$(BUILDDIR)/stackTest: $(BUILDDIR)/stackTest.o $(BUILDDIR)/stack.o $(BUILDDIR)/SingleLinkedList.o
	$(CC) $(BUILDDIR)/stackTest.o $(BUILDDIR)/SingleLinkedList.o $(BUILDDIR)/stack.o $(CFLAGS) -o $(BUILDDIR)/stackTest

$(BUILDDIR)/stackTest.o: $(BUILDDIR)/stack.o $(BUILDDIR)/SingleLinkedList.o $(TCODEDIR)/stackTest.c
	$(CC) -c $(TCODEDIR)/stackTest.c $(CFLAGS) -o $(BUILDDIR)/stackTest.o

install : fcalc
	cp $(BUILDDIR)/fcalc $(INSTDIR)
clean : 
	rm -f $(EXE)
	rm -f $(ALLOFILES)
	rm -f gmon.out
