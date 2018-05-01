#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "tokenizer.h"
#include "wordlink.h"
#include "codebuf.h"

#define INLINE_MACROS

#define COMPILE() codebuf_append(mode == MODE_MACRO \
		? &machine->macros \
		: &machine->program, ins)


enum mode {
	MODE_NORMAL,
	MODE_NAME,
	MODE_MACRO,
	MODE_COMMENT,
};

int compiler_compile(
		struct machine *machine,
		struct wordlink **words,
		char *program,
		int doend)
{
	int i;
	char *token;
	enum mode mode;
	struct instruction ins;
	char *endptr;
	DTYPE val;
	size_t len;
	int address;
	struct tokenizer tokenizer;
	int comment;

	comment = 0;
	mode = MODE_NORMAL;
	tokenizer_init(&tokenizer);
	len = strlen(program);

	for (i = 0; i < len + 1; i++) {
		token = tokenizer_get(&tokenizer, program[i]);
		if (!token) continue;

		if (mode == MODE_NAME) {
			ins.type = INS_PRGM;
			ins.data.program = machine->macros.head - machine->macros.start;
			wordlink_add(words, token, ins);
			mode = MODE_MACRO;
			continue;
		}

		if (comment) {
			if (token[strlen(token) - 1] == ')') {
				comment = 0;
			}
			continue;
		}

		if (strcmp(token, "(") == 0) {
			comment = 1;
			continue;
		}

		if (strcmp(token, ":") == 0) {
			if (mode == MODE_NAME || mode == MODE_MACRO) return -1;
			mode = MODE_NAME;
			continue;
		}

		if (strcmp(token, ";") == 0) {
			if (mode != MODE_MACRO) return -1;
			ins.type = INS_END;
			codebuf_append(&machine->macros, ins);
			mode = MODE_NORMAL;
			continue;
		}

		/* Find word by name */
		ins = wordlink_find(mode == MODE_MACRO
				? (*words)->prev
				: *words, token);

		/* If found... */
		if (ins.type != INS_NONE) {
#ifdef INLINE_MACROS
			/* If macro, Copy instructions instead */
			if (ins.type == INS_PRGM) {
				address = ins.data.program;
				ins = machine->macros.start[address];
				while (ins.type != INS_END) {
					COMPILE();
					ins = machine->macros.start[++address];
				}
				continue;
			}
#endif
			COMPILE();
			continue;
		} 

		val = strtof(token, &endptr);
		if (*endptr != '\0' || endptr == token) {
			fprintf(stderr, "Word \"%s\" not found\n", token);
			return -1;
		}

		ins.type = INS_PUSH;
		ins.data.value = val;
		COMPILE();
	}

	if (mode != MODE_NORMAL) return -1;

	if (doend) {
		ins.type = INS_END;
		codebuf_append(&machine->program, ins);
	}

	return 0;
}
