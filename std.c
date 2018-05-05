#include <stdio.h>
#include <math.h>

#include "types.h"
#include "machine.h"
#include "stack.h"
#include "wordlink.h"
#include "instruction.h"
#include "std.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define REGISTER(_name, _fun) do { \
	ins.data.function = _fun; \
	wordlink_add(words, _name, ins); \
} while (0)

#define POP() stack_pop(&m->dstack)
#define PUSH(_val) stack_push(&m->dstack, (_val))

static void add(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a + b);
}

static void sub(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a - b);
}

static void mul(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a * b);
}

static void div(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(b == 0.0f ? 0.0f : a / b);
}

static void swap(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(b);
	PUSH(a);
}

static void dup(struct machine *m)
{
	DTYPE a;
	a = POP();
	PUSH(a);
	PUSH(a);
}

static void rot(struct machine *m)
{
	DTYPE a, b, c;
	c = POP();
	b = POP();
	a = POP();
	PUSH(b);
	PUSH(c);
	PUSH(a);
}

static void drop(struct machine *m)
{
	POP();
}

static void print(struct machine *m)
{
	fprintf(stderr, "%f\n", POP());
}

static void printstack(struct machine *m)
{
	int i;
	for (i = 0; i < m->dstack.index; i++) {
		fprintf(stderr, "%f ", m->dstack.elems[i]);
	}
	printf("\n");
}

static void push(struct machine *m)
{
	stack_push(&m->rstack, POP());
}

static void pop(struct machine *m)
{
	PUSH(stack_pop(&m->rstack));
}

static void rat(struct machine *m)
{
	DTYPE a;
	a = stack_pop(&m->rstack);
	PUSH(a);
	stack_push(&m->rstack, a);
}

static void over(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a);
	PUSH(b);
	PUSH(a);
}

static void twodup(struct machine *m) {
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a);
	PUSH(b);
	PUSH(a);
	PUSH(b);
}

static void minusrot(struct machine *m)
{
	DTYPE a, b, c;
	c = POP();
	b = POP();
	a = POP();
	PUSH(c);
	PUSH(a);
	PUSH(b);
}

#define TF(_expr) ((_expr) ? 1.0f : 0.0f)

static void equals(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a == b));
}

static void nequals(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a != b));
}

static void lthan(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a < b));
}

static void gthan(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a > b));
}

static void lethan(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a <= b));
}

static void gethan(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a >= b));
}

static void booland(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a == 1.0f && b == 1.0f));
}

static void boolor(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(TF(a == 1.0f || b == 1.0f));
}

static void boolnot(struct machine *m)
{
	PUSH(TF(POP() == 0.0f));
}

static void insmin(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a < b ? a : b);
}

static void insmax(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(a > b ? a : b);
}

static void insmod(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(b == 0.0f ? b : fmod(fmod(a, b) + b, b));
}

static void inspow(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(pow(a, b));
}

static void insatan2(struct machine *m)
{
	DTYPE a, b;
	b = POP();
	a = POP();
	PUSH(atan2(a, b));
}

static void negate(struct machine *m)
{
	PUSH(-POP());
}

static void inssin(struct machine *m)
{
	PUSH(sin(POP()));
}

static void instan(struct machine *m)
{
	PUSH(tan(POP()));
}

static void inscos(struct machine *m)
{
	PUSH(cos(POP()));
}

static void inslog(struct machine *m)
{
	PUSH(log(POP()));
}

static void insexp(struct machine *m)
{
	PUSH(exp(POP()));
}

static void inssqrt(struct machine *m)
{
	PUSH(sqrt(POP()));
}

static void insfloor(struct machine *m)
{
	PUSH(floor(POP()));
}

static void insceil(struct machine *m)
{
	PUSH(ceil(POP()));
}

static void insabs(struct machine *m)
{
	PUSH(fabs(POP()));
}

static void inspi(struct machine *m)
{
	PUSH(M_PI);
}

static void zplus(struct machine *m)
{
	DTYPE a, b, c, d;
	d = POP();
	c = POP();
	b = POP();
	a = POP();
	PUSH(a + c);
	PUSH(b + d);
}

static void zmul(struct machine *m)
{
	DTYPE a, b, c, d;
	d = POP();
	c = POP();
	b = POP();
	a = POP();
	PUSH(a * c - b * d);
	PUSH(a * d + b * c);
}

static void insx(struct machine *m)
{
	PUSH(m->mem[STD_X_LOC]);
}

static void insy(struct machine *m)
{
	PUSH(m->mem[STD_Y_LOC]);
}

static void setwidth(struct machine *m)
{
	DTYPE a;
	a = POP();
	m->mem[STD_WIDTH_LOC] = a;
}

static void setheight(struct machine *m)
{
	DTYPE a;
	a = POP();
	m->mem[STD_HEIGHT_LOC] = a;
}

static void defaultt(struct machine *m)
{
	PUSH(0.0f);
}

void std_init(struct wordlink **words)
{
	struct instruction ins;

	ins.type = INS_CALL;

	REGISTER("x", insx);
	REGISTER("y", insy);

	REGISTER("swap", swap);
	REGISTER("dup", dup);
	REGISTER("rot", rot);
	REGISTER("drop", drop);
	REGISTER("over", over);
	REGISTER("2dup", twodup);
	REGISTER("-rot", minusrot);

	REGISTER("push", push);
	REGISTER(">r", push);
	REGISTER("r>", pop);
	REGISTER("r@", rat);

	REGISTER("=", equals);
	REGISTER("<>", nequals);
	REGISTER("<", lthan);
	REGISTER(">", gthan);
	REGISTER("<=", lethan);
	REGISTER(">=", gethan);

	REGISTER("and", booland);
	REGISTER("or", boolor);
	REGISTER("not", boolnot);

	REGISTER("min", insmin);
	REGISTER("max", insmax);

	REGISTER("+", add);
	REGISTER("-", sub);
	REGISTER("*", mul);
	REGISTER("/", div);
	REGISTER("mod", insmod);
	REGISTER("negate", negate);

	REGISTER("z+", zplus);
	REGISTER("z*", zmul);

	REGISTER("pow", inspow);
	REGISTER("**", inspow);
	REGISTER("log", inslog);
	REGISTER("exp", insexp);
	REGISTER("sqrt", inssqrt);

	REGISTER("floor", insfloor);
	REGISTER("ceil", insceil);
	REGISTER("abs", insabs);

	REGISTER("atan2", insatan2);
	REGISTER("sin", inssin);
	REGISTER("cos", inscos);
	REGISTER("tan", instan);

	REGISTER("pi", inspi);

	REGISTER(".", print);
	REGISTER(".s", printstack);
	REGISTER("width", setwidth);
	REGISTER("height", setheight);
	REGISTER("t", defaultt);
}
