CC=gcc # gcc-10 for macOS
CFLAGS=-fsanitize=address -Wvla -Wall -Werror -g -std=gnu11 -lasan
TARGET=timetable

all: $(TARGET)

timetable: timetable.c
	$(CC) $(CFLAGS) $^ -o $@

# add environment var
test: export ASAN_OPTIONS=verify_asan_link_order=0

test: timetable
	bash test.sh

clean:
	rm timetable
	rm -r *.dSYM
