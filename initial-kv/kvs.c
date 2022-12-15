#include "kvs.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Replicate of `strdup(3)`
 *
 * @deprecated Do not use this one. This is a reference on how `strdup` is
 * written.
 */
char *
__strdup(const char *str)
{
	size_t len = strlen(str) + 1;
	char *dup  = (char *)malloc(sizeof(char) * len);

	if (dup == (char *)0)
		return (char *)0;

	return (char *)memcpy(dup, str, len);
}

struct pair_t *
parsepair(const char *str)
{

	// Since `strsep(3)` will modify the string pointer, duplicate the passed-in
	// string to avoid losing data. Since `dup` is dynamically allocated, it has
	// to be freed to avoid memory leak (see `strdup(3)`). But `strsep(3)` will
	// modify it, thus create `end` for `strsep(3)` while keep `dup` for
	// `free(3)`.
	char *dup			= strdup(str);
	char *end			= dup;
	struct pair_t *pair = NULL;

	char *key	= strsep(&end, ",");
	char *value = strsep(&end, ",");

	if (!key && !value)
	{
		fprintf(stderr, "cannot parse line");
		exit(EXIT_FAILURE);
	}

	pair	  = (struct pair_t *)malloc(sizeof(struct pair_t));
	pair->key = strdup(key);
	pair->val = strdup(value);

	free(dup);
	return pair;
}

void
freepair(struct pair_t *pair)
{
	free(pair->key);
	free(pair->val);
	free(pair);
}
