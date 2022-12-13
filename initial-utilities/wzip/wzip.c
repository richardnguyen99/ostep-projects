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
writerle(struct rle_t rleobj)
{
	// Use fwrite to write binary stream to stdout.
	fwrite((int *)(&(rleobj.l)), sizeof(int), 1, stdout);
	fwrite((char *)(&(rleobj.c)), sizeof(char), 1, stdout);
}

/**
 * @brief Run-length encoding
 *
 * @param stream File stream to read.
 * @param prev  Previous RLE object from previous streams.
 * @return struct rle_t for next file stream to use.
 */
struct rle_t
process(FILE *stream, struct rle_t prev)
{
	int curr;
	struct rle_t rle;

	while ((curr = fgetc(stream)) != EOF)
	{
		// Start to write binary format of RLE objects when the current
		// character doesn't match with the previous one.
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

	// Finish the RLE for the last occurrence.
	writerle(prev);

	return 0;
}