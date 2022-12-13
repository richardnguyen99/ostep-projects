/**
 * @file wzip.c
 * @author RIchard Nguyen (richard@richardhnguyen.com)
 * @brief Simple compression program.
 * @version 0.2
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// FILE, stdout, fprintf, fwrite, fgetc, EOF, fclose
#include <stdlib.h> // EXIT_*, exit

struct rle_t
{
	int l;
	char c;
};

void
writerle(struct rle_t rleobj)
{
	fwrite((int *)(&(rleobj.l)), sizeof(int), 1, stdout);
	fwrite((char *)(&(rleobj.c)), sizeof(char), 1, stdout);
}

struct rle_t
process(FILE *stream, struct rle_t prev)
{
	int curr;
	struct rle_t rle;

	while ((curr = fgetc(stream)) != EOF)
	{
		if (prev.c != '\0' && curr != prev.c)
		{
			rle.c  = prev.c;
			rle.l  = prev.l;
			prev.l = 0;

			writerle(rle);
		}

		prev.l++;
		prev.c = curr;
	}

	rle.c = prev.c;
	rle.l = prev.l;

	return rle;
}

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "wzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	}

	struct rle_t prev;
	prev.c = '\0';
	prev.l = 0;

	for (int i = 1; i < argc; ++i)
	{

		FILE *fp = fopen(argv[i], "r");

		if (fp == NULL)
		{
			fprintf(stdout, "wzip: cannot open files\n");
			exit(EXIT_FAILURE);
		}

		struct rle_t rle = process(fp, prev);
		prev.c			 = rle.c;
		prev.l			 = rle.l;

		fclose(fp);
	}

	writerle(prev);

	return 0;
}