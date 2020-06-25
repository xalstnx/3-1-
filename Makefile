CC=gcc
CFLAGS=-o
TARGETS=client server
all: $(TARGETS)
.PHONY: all
%:
	$(CC) -g -o $@ $@.c 
       
clean:
	rm $(TARGETS)
