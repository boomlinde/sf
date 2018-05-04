#include <string.h>

#include "tokenizer.h"

void tokenizer_init(struct tokenizer *tokenizer)
{
	tokenizer->wordbuf[0] = '\0';
	tokenizer->wordbuf[MAXNAME-1] = '\0';
	tokenizer->bufp = tokenizer->wordbuf;
}

char *tokenizer_get(struct tokenizer *tokenizer, char c)
{
	switch (c) {
	case '\n':
	case '\r':
	case ' ':
	case '\t':
	case 0:
		*tokenizer->bufp = 0;
		tokenizer->bufp = tokenizer->wordbuf;
		return *tokenizer->bufp ? tokenizer->wordbuf : 0;
	default:
		if (tokenizer->wordbuf - tokenizer->bufp < MAXNAME - 1) {
			*tokenizer->bufp = c;
			tokenizer->bufp++;
		}
		return NULL;
	}
}
