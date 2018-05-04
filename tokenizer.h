#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "types.h"

struct tokenizer {
	char wordbuf[MAXNAME];
	char *bufp;
};

void tokenizer_init(struct tokenizer *tokenizer);
char *tokenizer_get(struct tokenizer *tokenizer, char c);

#endif /* _TOKENIZER_H_ */
