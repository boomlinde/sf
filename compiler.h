#ifndef _COMPILER_H_
#define _COMPILER_H_

int compiler_compile(
		struct machine *machine,
		struct wordlink **words,
		char *program,
		int doend);

#endif /* _COMPILER_H_ */
