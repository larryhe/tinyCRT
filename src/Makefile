#marco(variables) definition. here are some special marcos 
#$@ name of target to be made
#$< name of related file that cause the action 
CC=gcc
AR=ar
LD=ld
CFLAGS=-c -fno-builtin -nostdlib -fno-stack-protector 
LDFLAGS=-static -e tiny_crt_entry
SOURCES=entry.c malloc.c stdio.c string.c printf.c test.c
#special macro replace all the suffix(.c) in SOURCES with .o
OBJECTS=$(SOURCES:.c=.o)
AROBJS=malloc.o printf.o stdio.o string.o
LIBNAME=tinycrt.a
test: archive
	$(LD) $(LDFLAGS) entry.o test.o $(LIBNAME) -o $@
archive: $(SOURCES) $(OBJECTS)
	$(AR) -rs $(LIBNAME) $(AROBJS)
#suffix rule in form of (.FROM.TO)
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(LIBNAME) test
