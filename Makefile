# Makefile for filter program

CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

filter: filter.c helpers.c helpers.h bmp.h
	$(CC) $(CFLAGS) -o filter filter.c helpers.c

clean:
	rm -f filter *.o
