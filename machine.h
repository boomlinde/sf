#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "types.h"

void machine_init(struct machine *m);
void machine_free(struct machine *m);
void machine_reset(struct machine *m);

#endif /* _MACHINE_H_ */
