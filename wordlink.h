#ifndef _WORDLINK_H_
#define _WORDLINK_H_

#include "instruction.h"

void wordlink_add(
		struct wordlink **head,
		const char *name,
		const struct instruction ins);

void wordlink_free(struct wordlink **head);

struct instruction
wordlink_find(struct wordlink *head, const char *name);

#endif /* _WORDLINK_H_ */
