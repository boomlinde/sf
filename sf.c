#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "instruction.h"
#include "wordlink.h"
#include "stack.h"
#include "codebuf.h"
#include "machine.h"
#include "compiler.h"
#include "std.h"
#include "readfile.h"

#define DEFAULT_WIDTH 256
#define DEFAULT_HEIGHT 256

struct colorf {
	DTYPE r;
	DTYPE g;
	DTYPE b;
};

struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

static struct color getcolor(struct stack *stack)
{
	struct colorf c;
	struct color out;
	switch (stack->index) {
	case 0:
		c.r = 0; c.g = 0; c.b = 0;
		break;
	case 1:
		c.r = stack_pop(stack); c.g = 0; c.b = 0;
		break;
	case 2:
		c.g = stack_pop(stack); c.r = stack_pop(stack); c.b = 0;
		break;
	default:
		c.b = stack_pop(stack);
		c.g = stack_pop(stack);
		c.r = stack_pop(stack);
		break;
	}

	c.r = c.r > 1.0 ? 1.0 : c.r < 0.0 ? 0.0 : c.r;
	c.g = c.g > 1.0 ? 1.0 : c.g < 0.0 ? 0.0 : c.g;
	c.b = c.b > 1.0 ? 1.0 : c.b < 0.0 ? 0.0 : c.b;

	out.r = (int)(c.r * 255);
	out.g = (int)(c.g * 255);
	out.b = (int)(c.b * 255);
	return out;
}

int main(int argc, char **argv)
{
	static struct machine m;
	static struct wordlink *words;
	static struct instruction *insp;
	static char *program;
	static int res;
	struct color c;
	static int x, y;
	int width, height;

	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: %s [INIT] FILENAME\n", argv[0]);
		return -1;
	}

	machine_init(&m);

	program = readfile(argv[argc == 2 ? 1 : 2]);
	if (program == 0) {
		fprintf(stderr, "Can't read file \"%s\"\n", argv[argc == 2 ? 1 : 2]);
		res = -1;
		goto out;
	}

	std_init(&words);

	if (argc == 3) {
		res = compiler_compile(&m, &words, argv[1], 0);
		if (res) goto out;
	}

	res = compiler_compile(&m, &words, program, 1);
	if (res) goto out;

	wordlink_free(&words);

	/* Get width and height from dry run */
	m.mem[STD_WIDTH_LOC] = DEFAULT_WIDTH;
	m.mem[STD_HEIGHT_LOC] = DEFAULT_HEIGHT;
	insp = m.program.start;
	while (insp->type != INS_END) {
		instruction_execute(*insp++, &m);
	}
	width = m.mem[STD_WIDTH_LOC];
	height = m.mem[STD_HEIGHT_LOC];
	m.dstack.index = 0;
	m.rstack.index = 0;

	printf("P3\n%d %d\n255\n", width, height);
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			m.mem[0] = x / (DTYPE)width;
			m.mem[1] = y / (DTYPE)height;

			m.dstack.index = 0;
			m.rstack.index = 0;
			insp = m.program.start;
			while (insp->type != INS_END) {
				instruction_execute(*insp++, &m);
			}

			c = getcolor(&m.dstack);
			printf("%d %d %d\n", c.r, c.g, c.b);
		}
	}


out:
	wordlink_free(&words);
	machine_free(&m);
	free(program);
	return res;
}
