CFLAGS += -Wall -Wextra -Wpedantic -Werror

# Make sure we don't use variable length arrays by accident
CFLAGS += -Werror=vla

ifneq ($(findstring clang,$(shell $(CC) --version)),)
CFLAGS += -Weverything
endif

TEST_CFLAGS := \
    $(CFLAGS) \
    -fsanitize=address \
    -fsanitize=undefined \
    -fstack-protector-strong

.PHONY: example
example: CFLAGS=$(TEST_CFLAGS)
example: test
	./test 10000 2 100

test: test.o cprogbar.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: cross-build
cross-build: cprogbar.c
	$(CC) $(CFLAGS) -c cprogbar.c -o cprogbar-cross.o
	size -t cprogbar-cross.o

.PHONY: clean
clean:
	rm -rf *.o test
