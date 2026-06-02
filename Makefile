CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fPIC -Iinclude
LDFLAGS = -shared

SRC = src/poly.c
OBJ = poly.o
LIB = libpoly.so

TEST_C = tests/test_c.c
TEST_BIN = test_app

.PHONY: all clean shared app run syntax analyze sanitize test docs

all: shared app

shared: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIB) $(SRC)

app: $(TEST_C) shared
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_C) -L. -lpoly -Wl,-rpath,.

run: app
	./$(TEST_BIN)

test: run

syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(SRC) $(TEST_C)

analyze:
	$(CC) $(CFLAGS) -fanalyzer -c $(SRC)

sanitize: CFLAGS += -fsanitize=address,undefined -g
sanitize: clean app run

docs:
	doxygen Doxyfile

clean:
	rm -f *.o *.so $(TEST_BIN)
	rm -rf docs/html docs/latex
