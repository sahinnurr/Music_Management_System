CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Define the source and header files
SRCS = main.c song.c
OBJS = $(SRCS:.c=.o)
HEADERS = song.h

# Define the executable name
EXEC = music_manager

# Default target
all: $(EXEC)

# Linking the object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rule for source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up intermediate files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
