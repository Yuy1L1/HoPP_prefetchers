# Makefile

CC = gcc
CFLAGS = -g -Wall -Werror -O3 

# Source files
SRCS = main.c dominator.c ladder.c hopp_prefetcher.c # ripple.c (not implemented yet)
OBJS = main.o dominator.o ladder.o hopp_prefetcher.o # ripple.o (not implemented yet)

# Build the main executable
main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

# Compile individual object files
main.o: main.c dominator.h ladder.h hopp_prefetcher.h
	$(CC) $(CFLAGS) -c main.c

dominator.o: dominator.c dominator.h hopp_prefetcher.h
	$(CC) $(CFLAGS) -c dominator.c

ladder.o: ladder.c ladder.h hopp_prefetcher.h
	$(CC) $(CFLAGS) -c ladder.c

hopp_prefetcher.o: hopp_prefetcher.c hopp_prefetcher.h
	$(CC) $(CFLAGS) -c hopp_prefetcher.c

# Placeholder for ripple (commented out)
#ripple.o: ripple.c ripple.h hopp_prefetcher.h
#	$(CC) $(CFLAGS) -c ripple.c

# Clean command
clean:
	rm -rf *.o main

