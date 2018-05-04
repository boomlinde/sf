#include <stdlib.h>
#include <stdio.h>

#include "readfile.h"

char *readfile(char *filename)
{
	FILE *f;
	int res;
	char *content;
	size_t length;
	size_t readsize;

	content = 0;

	f = fopen(filename, "r");
	if (f == 0) return content;

	res = fseek(f, 0, SEEK_END);
	if (res) goto out;

	length = ftell(f);

	content = malloc(length * sizeof(char) + 1);
	if (!content) goto out;
	content[length] = '\0';

	res = fseek(f, 0, SEEK_SET);
	if (res) goto freecontent;

	readsize = fread(content, sizeof(char), length, f);
	if (readsize != length) goto freecontent;

	goto out;

freecontent:
	free(content);
out:
	fclose(f);
	return content;
}
