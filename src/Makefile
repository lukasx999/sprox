CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c11 -pedantic -fsanitize=address,undefined

BIN=compiler

DEPS=\
util.h        \
lexer.h       \
parser.h      \
gen.h 	      \
backend.h     \
symboltable.h \
types.h       \
grammar.h     \
ast.h         \
main.h        \

SOURCES=\
lexer.o       \
parser.o      \
gen.o         \
backend.o     \
util.o        \
types.o       \
symboltable.o \
grammar.o     \
ast.o         \


all: compiler

compiler: main.o $(SOURCES)
	@$(CC) $(CFLAGS) $^ -o $(BIN)
	@echo LINK $^

test: tests/test.o $(SOURCES)
	@$(CC) $(CFLAGS) $^ -o test
	@echo CC $^
	@./test
	@rm test
	@rm $<

memtest:
	@./tests/memtest.sh ./$(BIN) ./example/main.spx

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo CC $<

clean:
	rm *.o $(BIN)

.PHONY: clean, memtest
