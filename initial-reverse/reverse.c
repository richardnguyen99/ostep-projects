/**
 * @file reverse.c
 * @author Richard Nguyen (richard@richardhnguyen.com)
 * @brief A simple stream-reversing program.
 * @version 0.4
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>	// FILE, stdout, fprintf, fclose
#include <stdlib.h> // EXIT_*, exit
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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

void
swap(char **lines, size_t i, size_t j)
{
	char *tmp = lines[i];
	lines[i]  = lines[j];
	lines[j]  = tmp;
}

void
inplace_reverse(char **lines, size_t n)
{
	size_t mid = n / 2;

	for (size_t i = 0; i < mid; ++i)
		swap(lines, i, n - i - 1);
}

int
check_inode(const char *f1, const char *f2)
{
	struct stat buf1 = {0};
	lstat(f1, &buf1);

	struct stat buf2 = {0};
	lstat(f2, &buf2);

	return buf1.st_ino == buf2.st_ino;
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

	FILE *ifstream = stdin;
	FILE *ofstream = stdout;

	if (argv[1])
	{
		ifstream = fopen(argv[1], "r");

		if (ifstream == NULL)
		{
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	if (ifstream != stdin && argv[2])
	{
		if (strcmp(argv[1], argv[2]) == 0)
		{
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(EXIT_FAILURE);
		}

		if (check_inode(argv[1], argv[2]))
		{
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(EXIT_FAILURE);
		}

		ofstream = fopen(argv[2], "w+");

		if (ofstream == NULL)
		{
			fprintf(stderr, "reverse: cannot open files\n");
			exit(EXIT_FAILURE);
		}
	}

	lines = getlines(ifstream, &cnt, &cap);
	inplace_reverse(lines, cnt);

	for (size_t i = 0; i < cnt; ++i)
	{
		fprintf(ofstream, "%s", lines[i]);
		free(lines[i]);
	}

	if (ifstream != stdin)
		fclose(ifstream);
	if (ofstream != stdout)
		fclose(ofstream);

	free(lines);

	return 0;
}