/**
 * @file wunzip.c
 * @author RIchard Nguyen (richard@richardhnguyen.com)
 * @brief Simple decompression program.
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// FILE, stdout, fprintf, fwrite, fgetc, EOF, fclose
#include <stdlib.h> // EXIT_*, exit

/**
 * @brief Structure for run-length encoding to keep track the repetition and the
 * character.
 */
struct rle_t
{
	int l;	// Run-length
	char c; // Character
};

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "wunzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i < argc; ++i)
	{

		FILE *fp = fopen(argv[i], "r");

		if (fp == NULL)
		{
			fprintf(stdout, "wunzip: cannot open files\n");
			exit(EXIT_FAILURE);
		}

		fclose(fp);
	}

	return 0;
}