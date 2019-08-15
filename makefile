LIBS = -lm `pkg-config sdl2 --cflags` `pkg-config sdl2 --libs`
CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi $(LIBS)
DEBUG = -g3
OPTIM = -O2
VALGRIND = --error-exitcode=1 --quiet --leak-check=full

all: parse interp extension

parse: parser.c parser.h parsertest.c
	$(CC) parser.c parsertest.c -o parse $(CFLAGS) $(DEBUG) -include parser.h

interp: interpreter.c interpreter.h interpretertest.c neillsdl2.c
	$(CC) interpreter.c interpretertest.c neillsdl2.c -o interp $(CFLAGS) $(OPTIM) -include interpreter.h

extension: extension.c extension.h extensiontest.c neillsdl2.c
	$(CC) extension.c extensiontest.c neillsdl2.c -o extension $(CFLAGS) $(OPTIM) -include extension.h

run: all
	./parse
	./interp
	./extension

clean:
	rm -f parse interp extension

.PHONY: clean run all
