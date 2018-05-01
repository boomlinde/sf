#ifndef _CODEBUF_H_
#define _CODEBUF_H_

#include "types.h"

struct codebuf codebuf_new(unsigned int initial_size);
void codebuf_append(struct codebuf *buf, struct instruction ins);
void codebuf_execute(struct codebuf *buf, struct machine *machine);
void codebuf_free(struct codebuf *buf);

#endif /* _CODEBUF_H_ */
