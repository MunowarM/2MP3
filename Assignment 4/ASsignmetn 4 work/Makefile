# Compiler and flags
CC = gcc
CFLAGS = -Ofast -lm

# Source files
SOURCES = main.c PSO.c OF.c
HEADERS = utility.h OF_lib.h
EXECUTABLE = pso

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(EXECUTABLE)
