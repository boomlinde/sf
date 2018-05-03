#include <string.h>
#include <stdlib.h>

#include "wordlink.h"
#include "types.h"

void wordlink_add(
		struct wordlink **head,
		const char *name,
		const struct instruction ins)
{
	struct wordlink *new;

	new = malloc(sizeof(struct wordlink));

	new->ins = ins;
	strcpy(new->name, name);
	new->prev = *head;
	*head = new;
}

void wordlink_free(struct wordlink **head)
{
	struct wordlink *tmp;

	while (*head) {
		tmp = (*head)->prev;
		free(*head);
		*head = tmp;
	}
}

struct instruction
wordlink_find(struct wordlink *head, const char *name)
{
	struct instruction ret;
	while (head) {
		if (strcmp(head->name, name) == 0) return head->ins;
		head = head->prev;
	}

	ret.type = INS_NONE;

	return ret;
}

