#include <stdio.h>

#include "types.h"
#include "stack.h"
#include "instruction.h"
#include "machine.h"
#include "codebuf.h"

void instruction_execute(
		struct instruction ins,
		struct machine *machine)
{
	struct instruction *pc;

	switch (ins.type) {
	case INS_NONE:
	case INS_END:
		/* do nothing */
		break;
	case INS_PUSH:
		stack_push(&machine->dstack, ins.data.value);
		break;
	case INS_CALL:
		ins.data.function(machine);
		break;
	case INS_PRGM:
		pc = &machine->macros.start[ins.data.program];
		while (pc->type != INS_END) {
			instruction_execute(*pc, machine);
			pc++;
		}
		break;
	}
}
