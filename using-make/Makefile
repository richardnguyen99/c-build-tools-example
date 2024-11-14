# Compiler options
# gcc for C source code
CC=gcc
INCLUDEDIR=include
SRCDIR=src

# Optimized and fully warnings
CFLAGS=-Wall -Wextra -Werror -O3

# For debugging and testing only
DEBUGS=-DDEBUG -g -O0

# Include directory
INCLUDE=-I./$(INCLUDEDIR)

# Short - Compile all
all: whoisserver whoisclient

# Use to debug and test. This will display some useful message and provide quick
# development. However do not use for grading as it might not cover all hidden
# bugs.
debug: 
	$(CC) $(DEBUGS) $(INCLUDE) src/whoisclient.c src/whois.c -o whoisclient_debug
	$(CC) $(DEBUGS) $(INCLUDE) src/whoisserver.c src/whois.c -o whoisserver_debug

whoisclient: whois.o whoisclient.o
	$(CC) $(CFLAGS) $(INCLUDE) whoisclient.o whois.o -o whoisclient

whoisserver: whois.o whoisserver.o
	$(CC) $(CFLAGS) $(INCLUDE) whoisserver.o whois.o -o whoisserver

# Compile all the source code to object files
%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o whoisclient whoisserver whoisclient_debug whoisserver_debug
