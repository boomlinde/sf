#include "types.h"
#include "stack.h"
#include "types.h"

void stack_push(struct stack *stack, DTYPE val)
{
	stack->elems[stack->index++] = val;
}

DTYPE stack_pop(struct stack *stack)
{
	return stack->elems[--stack->index];
}
