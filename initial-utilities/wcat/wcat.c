/**
 * @file wcat.c
 * @author Richard Nguyen (richard@richardhnguyen.com)
 * @brief Replicate version of Unix's cat
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 */

#include <stddef.h> // NULL
#include <stdio.h> // stdout, stderr, FILE, fopen, fclose, fprintf, fgets, fputs
#include <stdlib.h> // exit, EXIT_SUCCESS, EXIT_FAILURE

void
fhandle(FILE *fp)
{
	char str[80];
	if (fp == NULL)
	{
		// It's best practice to check if a file is opened
		// successfully. For this project, we still need to
		// check regarding the requirements.
		fprintf(stdout, "wcat: cannot open file\n");
		exit(EXIT_FAILURE);
	}

	// Keep reading the file, opening in fd, until it hits a null
	// terminator, \0. On success, read string is stored in `str`.
	// On error or when finished, NULL is returned instead. More on
	// `man 3 fgets`.
	while (fgets(str, 80, fp) != NULL)
		fputs(str, stdout); // or fprintf(stdout, "%s", str);
}

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		/**
		 * The original version of cat, UNIX's cat, will instead read
		 * from `stdin` line-by-line, and print the content on the next
		 * line. For this problem, that case is ignored.
		 */
		exit(EXIT_SUCCESS);
	}

	for (int i = 1; i < argc; ++i)
	{
		FILE *fp = fopen(argv[i], "r");

		fhandle(fp);
		fclose(fp);
	}

	return 0;
}