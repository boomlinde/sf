#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

struct tokenizer {
	char wordbuf[256];
	char *bufp;
};

void tokenizer_init(struct tokenizer *tokenizer);
char *tokenizer_get(struct tokenizer *tokenizer, char c);

#endif /* _TOKENIZER_H_ */
