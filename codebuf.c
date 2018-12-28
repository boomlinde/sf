#include <string.h>
#include <stdlib.h>

#include "instruction.h"
#include "machine.h"
#include "codebuf.h"

static int grow(struct codebuf *buf)
{
	unsigned int offset;

	buf->size <<= 1;
	offset = buf->head - buf->start;
	buf->start = realloc(buf->start, buf->size * sizeof(struct instruction));
	buf->head = buf->start + offset;

	return buf->start != NULL;
}

int codebuf_new(struct codebuf *buf, size_t initial_size)
{
	buf->start = malloc(initial_size * sizeof(struct instruction));
	buf->head = buf->start;
	buf->size = initial_size;

	return buf->start != NULL;
}

int codebuf_append(struct codebuf *buf, struct instruction ins)
{
	if (buf->head == buf->start + buf->size) {
		if (!grow(buf)) return 0;
	}
	*buf->head = ins;
	buf->head++;

	return 1;
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
	buf->start = NULL;
}
