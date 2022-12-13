/**
 * @file wunzip.c
 * @author RIchard Nguyen (richard@richardhnguyen.com)
 * @brief Simple decompression program.
 * @version 1.0
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

void
unzip(FILE *stream)
{
	size_t item_read = 0;
	int count;
	char c;

	// If it cannot read 4 bytes, it reaches EOF assuming the file is correctly
	// formatted.
	while ((item_read = fread(&count, sizeof(int), 1, stream)) == 1)
	{
		item_read = fread(&c, sizeof(char), 1, stream);

		for (int i = 0; i < count; i++)
			fprintf(stdout, "%c", c);
	}
}

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

		unzip(fp);
		fclose(fp);
	}

	return 0;
}