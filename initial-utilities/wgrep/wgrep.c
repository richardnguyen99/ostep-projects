/**
 * @file wgrep.c
 * @author Richard Nguyen (richard@richardhnguyen.com)
 * @brief Replicate version of Unix's grep
 * @version 0.2
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// stdout, fprintf
#include <stdlib.h> // EXIT_*, exit

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

	for (i = 0; *(s + i) != '\0'; ++i)
	{
		for (j = 0; *(p + j) != '\0' && *(s + i + j) == *(p + j); ++j)
			;

		if (*(p + j) == '\0')
			return i;
	}

	return -1;
}

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "wgrep: searchterm [file ...]\n");
		exit(EXIT_FAILURE);
	}

	if (find(argv[1], argv[2]) != -1)
		fprintf(stdout, "true\n");
	else
		fprintf(stdout, "false\n");

	return 0;
}