#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "types.h"
#include "machine.h"

void instruction_execute(
		struct instruction ins,
		struct machine *machine);

void instruction_print(struct instruction ins);

#endif /* _INSTRUCTION_H_ */
