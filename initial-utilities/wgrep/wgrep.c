/**
 * @file wgrep.c
 * @author Richard Nguyen (richard@richardhnguyen.com)
 * @brief Replicate version of Unix's grep
 * @version 1.0
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// stdout, fprintf
#include <stdlib.h> // EXIT_*, exit

#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief Naive string searching algorithm
 *
 * @param s Search string
 * @param p Search term
 * @return int Index of the first character in pattern p in string s if found.
 * Otherwise, -1.
 *
 * This naive solution will iterate through every character in s. If that
 * current character appears as the first character on the search pattern, the
 * comparision continues to the end of the search pattern.
 *
 * At the end of the comparision, if the whole string of search pattern is
 * iterated, it means a pattern is found. Otherwise, the process continues.
 */
int
find(const char *s, const char *p)
{
	int i = 0;
	int j = 0;

	if (*p == '\0')
		return 0;

	for (i = 0; *(s + i) != '\0'; ++i)
	{
		for (j = 0; *(p + j) != '\0' && *(s + i + j) == *(p + j); ++j)
			;

		if (*(p + j) == '\0')
			return i;
	}

	return -1;
}

void
printmatch(const char *s, long nread, const char *p)
{
	if (find(s, p) != -1)
		fwrite(s, nread, 1, stdout);
}

void
process(FILE *stream, char **lineptr, const char *pattern)
{
	size_t len = 0;
	long nread = 0;

	while ((nread = getline(lineptr, &len, stream)) != -1)
		printmatch(*lineptr, nread, pattern);

	free(*lineptr);
}

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "wgrep: searchterm [file ...]\n");
		exit(EXIT_FAILURE);
	}

	char *line = NULL;

	// No file is specified. Read from stdin
	if (argc == 2)
	{
		process(stdin, &line, argv[1]);

		return 0;
	}

	for (int i = 2; i < argc; ++i)
	{
		FILE *fp = fopen(argv[i], "r");

		if (fp == NULL)
		{
			fprintf(stdout, "wgrep: cannot open file\n");
			exit(EXIT_FAILURE);
		}

		process(fp, &line, argv[1]);
		fclose(fp);
	}

	return 0;
}