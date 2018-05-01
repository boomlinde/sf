#include "machine.h"
#include "stack.h"
#include "machine.h"
#include "codebuf.h"

void machine_init(struct machine *m)
{
	m->dstack.index = 0;
	m->rstack.index = 0;
	m->macros = codebuf_new(128);
	m->program = codebuf_new(128);
}

void machine_free(struct machine *m)
{
	codebuf_free(&m->macros);
	codebuf_free(&m->program);
}

void machine_reset(struct machine *m)
{
	machine_free(m);
	machine_init(m);
}
