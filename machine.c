#include "machine.h"
#include "stack.h"
#include "machine.h"
#include "codebuf.h"

#define INITIAL_SIZE 2048

int machine_init(struct machine *m)
{
	m->dstack.index = 0;
	m->rstack.index = 0;
	if(!codebuf_new(&m->macros, INITIAL_SIZE)) return 0;
	if(!codebuf_new(&m->program, INITIAL_SIZE)) {
		codebuf_free(&m->macros);
		return 0;
	}

	return 1;
}

void machine_free(struct machine *m)
{
	codebuf_free(&m->macros);
	codebuf_free(&m->program);
}
