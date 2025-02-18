# Compiler to use
CC=gcc

# Compiler flags
CFLAGS=-Wall -g

# Executable name
TARGET=SentimentAnalyzer

# Source files
SOURCES=main.c vaderSentiment.c

# Object files
OBJECTS=$(SOURCES:.c=.o)

# Default target, default action is to build and run
default: build run

# Build the program
build: $(TARGET)

# Link the object files into the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Run the program
run:
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# This target tells make that these are not file names.
.PHONY: default build run clean
