#ifndef _CODEBUF_H_
#define _CODEBUF_H_

#include "types.h"

int codebuf_new(struct codebuf *buf, size_t initial_size);
int codebuf_append(struct codebuf *buf, struct instruction ins);
void codebuf_execute(struct codebuf *buf, struct machine *machine);
void codebuf_free(struct codebuf *buf);

#endif /* _CODEBUF_H_ */
