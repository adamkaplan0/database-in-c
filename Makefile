#
# File: Makefile
# Creator: Adam Kaplan
# Time-stamp: November 27, 2016
#

PROGRAMS = main
CFLAGS = -g

programs: $(PROGRAMS)


main: relation.o io.o

clean:
	-rm $(PROGRAMS) *.o
	-rm -r *.dSYM
