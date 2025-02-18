# Define variables
CC = gcc
CFLAGS = -O3 -shared -fPIC
TARGET = libmysort.so
SRC = mySort.c

# Rule to build the shared library
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Phony target to avoid conflicts with files named 'clean'
.PHONY: clean

# Rule to clean up generated files
clean:
	rm -f $(TARGET)
