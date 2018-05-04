#ifndef _TYPES_H_
#define _TYPES_H_

#define DTYPE float

#define MAXNAME 32

/* Needs to be power of two */
#define STACKSIZE (1 << 8)

struct stack;
struct machine;
struct instruction;
struct codebuf;
struct wordlink;

struct stack {
	DTYPE elems[STACKSIZE];
	int index;
};

struct codebuf {
	struct instruction *start;
	struct instruction *head;
	unsigned int size;
};

struct machine {
	struct stack dstack;
	struct stack rstack;
	struct codebuf macros;
	struct codebuf program;
	DTYPE mem[256];
};

enum instruction_type {
	INS_NONE,
	INS_END,
	INS_PUSH,
	INS_CALL,
	INS_PRGM
};

union instruction_data {
	DTYPE value;
	void (*function)(struct machine *m);
	int program;
};

struct instruction {
	enum instruction_type type;
	union instruction_data data;
};

struct wordlink {
	char name[MAXNAME];
	struct instruction ins;
	struct wordlink *prev;
};


#endif /* _TYPES_H_ */
