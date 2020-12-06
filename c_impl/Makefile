COMMON_FLAGS = -Wall -Wextra -Wpedantic

ifdef DEBUG
	CFLAGS = $(COMMON_FLAGS) -O0 -g
else
	CFLAGS = $(COMMON_FLAGS) -O3 -DNDEBUG
endif

all: listSlices_c

listSlices_c: src/main.o
	$(CC) $(CFLAGS) -o listSlices_c $^

.PHONY:

clean:
	rm -f src/main.o
	rm -f listSlices_c
