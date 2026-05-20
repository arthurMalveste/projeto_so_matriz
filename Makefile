CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = rotacionaMat

all: $(TARGET)

$(TARGET): rotacionaMat.c
	$(CC) $(CFLAGS) rotacionaMat.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.rot