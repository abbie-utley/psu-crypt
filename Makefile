#This is a Makefile backbone used by Mark Morrissey in his 201 class
#comes from web.cecs.pdx.edu/~markem/CS201/homework/Makefile
#hodgepodged with some code found on stack overflow at https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean

CC=gcc

#flag for debugging in gdb
DFLAGS=-g

#flag for warnings
CFLAGS=-c -Wall

#extra flags ig idk what LDflags are but oh well
LDFLAGS=-g

#source files for encryption
SOURCES_ENC=main_enc.c keyschedule.c wholesched.c FandG_function.c ftable.c

#source files for decryption
SOURCES_DEC=main_dec.c

#object files for encryption
OBJECTS_ENC=$(SOURCES_ENC:.c=.o)

#oject files for decryption
OBJECTS_DEC=$(SOURCES_DEC:.c=.o)

#executables
EXEC_ENC=encrypt
EXEC_DEC=decrypt

#make encryption the default
all: $(SOURCES_ENC) $(EXEC_ENC)

$(EXEC_ENC): $(OBJECTS_ENC)
	$(CC) $(DFLAGS) $(OBJECTS_ENC) -o $@

$(EXEC_DEC): $(OBJECTS_DEC)
	$(CC) $(DFLAGS) $(OBJECTS_DEC) -o $@

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f *.o ~*
