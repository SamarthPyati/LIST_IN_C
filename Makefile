CC=gcc
CFLAGS=-Wall 

TARGET=list

all: build run

build: list.c 
	$(CC) $(CFLAGS) -o $(TARGET) list.c

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
