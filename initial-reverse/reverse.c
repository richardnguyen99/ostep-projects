/**
 * @file reverse.c
 * @author Richard Nguyen (richard@richardhnguyen.com)
 * @brief A simple stream-reversing program.
 * @version 0.2
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// FILE, stdout, fprintf, fclose
#include <stdlib.h> // EXIT_*, exit
#include <string.h>

char **
linesalloc(char **oldptr, size_t size)
{
	char **newptr = (char **)realloc(oldptr, sizeof(char *) * size);

	if (newptr == NULL)
	{
		fprintf(stderr, "malloc error");
		exit(EXIT_FAILURE);
	}

	return newptr;
}

char **
getlines(FILE *stream, size_t *cnt, size_t *cap)
{
	char **lines = linesalloc(NULL, *cap);

	char *line	 = NULL;
	size_t nread = 0;
	size_t ncnt	 = 0;
	size_t ncap	 = *cap;

	while (getline(&line, &nread, stream) != -1)
	{
		lines[ncnt++] = line;
		line		  = NULL;

		if (nread == ncap - 1)
		{
			ncap <<= 1;
			lines = linesalloc(lines, ncap);
		}
	}

	*cnt = ncnt;
	*cap = ncap;

	free(line);
	return lines;
}

int
main(int argc, const char *argv[])
{
	if (argc > 3)
	{
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(EXIT_FAILURE);
	}

	size_t cap	 = 64;
	size_t cnt	 = 0;
	char **lines = NULL;

	if (argc == 2)
	{
		FILE *fp = fopen(argv[1], "r");

		if (fp == NULL)
		{
			fprintf(stderr, "reverse: cannot open files\n");
			exit(EXIT_FAILURE);
		}

		lines = getlines(fp, &cnt, &cap);
		fclose(fp);
	}

	for (size_t i = 0; i < cnt; ++i)
		free(lines[i]);
	free(lines);

	return 0;
}