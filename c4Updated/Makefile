# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Programs
PROGS = make_data_2d read_data_2d add_data_2d

all: $(PROGS)

make_data_2d: make_data_2d.c utilities.c
	$(CC) $(CFLAGS) -o $@ make_data_2d.c utilities.c

read_data_2d: read_data_2d.c utilities.c
	$(CC) $(CFLAGS) -o $@ read_data_2d.c utilities.c

add_data_2d: add_data_2d.c utilities.c
	$(CC) $(CFLAGS) -o $@ add_data_2d.c utilities.c

clean:
	rm -f $(PROGS)
