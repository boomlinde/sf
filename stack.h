#ifndef _STACK_H_
#define _STACK_H_

#include "types.h"

void stack_push(struct stack *stack, DTYPE val);
DTYPE stack_pop(struct stack *stack);

#endif /* _STACK_H_ */
