#include <string.h>
#include <stdlib.h>

#include "instruction.h"
#include "machine.h"
#include "codebuf.h"

static void grow(struct codebuf *buf)
{
	unsigned int offset;

	buf->size <<= 1;
	offset = buf->head - buf->start;
	buf->start = realloc(buf->start, buf->size * sizeof(struct instruction));
	buf->head = buf->start + offset;
}

struct codebuf codebuf_new(unsigned int initial_size)
{
	struct codebuf buf;

	buf.start = malloc(initial_size * sizeof(struct instruction));
	buf.head = buf.start;
	buf.size = initial_size;

	return buf;
}

void codebuf_append(struct codebuf *buf, struct instruction ins)
{
	if (buf->head == buf->start + buf->size) grow(buf);
	*buf->head = ins;
	buf->head++;
}

void codebuf_execute(struct codebuf *buf, struct machine *machine)
{
	struct instruction *pc;

	pc = buf->start;
	while (pc != buf->head) instruction_execute(*pc++, machine);
}

void codebuf_free(struct codebuf *buf)
{
	free(buf->start);
}
