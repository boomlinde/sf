LDFLAGS += -lm -s
CFLAGS += -O3 -std=c89 -Wpedantic -Wall -Wextra -Werror

sf: \
	sf.o \
	wordlink.o \
	instruction.o \
	stack.o \
	machine.o \
	codebuf.o \
	compiler.o \
	tokenizer.o \
	std.o \
	readfile.o

sf.o: \
	sf.c \
	types.h \
	instruction.h \
	wordlink.h \
	stack.h \
	codebuf.h \
	machine.h \
	compiler.h \
	std.h \
	readfile.h

wordlink.o: wordlink.c wordlink.h types.h

machine.o: machine.c machine.h stack.h machine.h codebuf.h

stack.o: stack.c types.h stack.h types.h

instruction.o: instruction.c types.h stack.h instruction.h machine.h codebuf.h

codebuf.o: codebuf.c instruction.h machine.h codebuf.h

compiler.o: compiler.c types.h tokenizer.h wordlink.h codebuf.h

tokenizer.o: tokenizer.c tokenizer.h

std.o: std.c types.h machine.h stack.h wordlink.h instruction.h std.h

readfile.o: readfile.c readfile.h

examples: \
	examples/spinner.gif \
	examples/twister.gif \
	examples/beeplasma.gif \
	examples/checker.gif \
	examples/rainbow.gif \
	examples/metadonut.gif \
	examples/mandelbrot.png \

examples/spinner.gif: sf sfgif examples/spinner.fs
	./sfgif examples/spinner.fs 50 2

examples/twister.gif: sf sfgif examples/twister.fs
	./sfgif examples/twister.fs 200 2

examples/beeplasma.gif: sf sfgif examples/beeplasma.fs
	./sfgif examples/beeplasma.fs 50 16

examples/checker.gif: sf sfgif examples/checker.fs
	./sfgif examples/checker.fs 50 2

examples/rainbow.gif: sf sfgif examples/rainbow.fs
	./sfgif examples/rainbow.fs 50 32

examples/metadonut.gif: sf sfgif examples/metadonut.fs
	./sfgif examples/metadonut.fs 400 32

examples/mandelbrot.png: sf sfgif examples/mandelbrot.fs
	./sf examples/mandelbrot.fs |convert - examples/mandelbrot.png

clean:
	-rm -f *.o examples/*.gif examples/*.png sf

