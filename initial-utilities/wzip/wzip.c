/**
 * @file wzip.c
 * @author RIchard Nguyen (richard@richardhnguyen.com)
 * @brief Simple compression program.
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "wzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i < argc; ++i)
	{

		FILE *fp = fopen(argv[i], "r");

		if (fp == NULL)
		{
			fprintf(stdout, "wzip: cannot open files\n");
			exit(EXIT_FAILURE);
		}

		int len = 38;
		char c	= 'a';
		fwrite((int *)(&len), sizeof(int), 1, stdout);
		fwrite((char *)(&c), sizeof(char), 1, stdout);

		fclose(fp);
	}

	return 0;
}