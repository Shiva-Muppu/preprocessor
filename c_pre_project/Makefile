CC = gcc
CFLAGS = -Wall

OBJS = main.o comment_removal.o macro_handler.o macro_replace.o file_inclusion.o

mypreprocessor.exe: $(OBJS)
	$(CC) $(CFLAGS) -o mypreprocessor.exe $(OBJS)

main.o: main.c comment_removal.h macro_handler.h macro_replace.h file_inclusion.h
	$(CC) $(CFLAGS) -c main.c

comment_removal.o: comment_removal.c comment_removal.h
	$(CC) $(CFLAGS) -c comment_removal.c

macro_handler.o: macro_handler.c macro_handler.h
	$(CC) $(CFLAGS) -c macro_handler.c

macro_replace.o: macro_replace.c macro_replace.h macro_handler.h
	$(CC) $(CFLAGS) -c macro_replace.c

file_inclusion.o: file_inclusion.c file_inclusion.h
	$(CC) $(CFLAGS) -c file_inclusion.c

clean:
	del /Q *.o mypreprocessor.exe

.PHONY: clean