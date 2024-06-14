CC=gcc
CFLAGS=-Wall 

TARGET=usage

all: run  

run: usage.c 
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

.PHONY: clean 
clean: 
	rm -rf $(TARGET) $(TARGET)
