INCLUDE_PATH=../include/
LIBRARY_PATH=../library/
INSTALL_PATH=./
CC=gcc
CFLAGS=-I$(INCLUDE_PATH) -g -Wall -c
CPPFLAGS=
LDFLAGS=-lpthread
TARGET=Thread_epoll_server
SRCFILE=$(wildcard *.c)
DESTFILE=$(patsubst %.c,%.o,$(SRCFILE))
RM=rm -rf

$(TARGET):$(DESTFILE)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

clean: 
	$(RM) $(DESTIFILE)
