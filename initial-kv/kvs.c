#include "kvs.h"

#include <stdio.h>
#include <string.h>

void
errorf(void *src, const char *msg)
{
	if (src == (void *)0)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

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

size_t
hash(unsigned char *str)
{
	size_t hashed = INIT_HASH_VALUE;
	unsigned char c;

	while ((c = *str++))
		hashed = ((hashed << 5) + hashed) + (size_t)c;

	return hashed;
}

struct pair_t
parsepair(const char *str)
{

	// Since `strsep(3)` will modify the string pointer, duplicate the passed-in
	// string to avoid losing data. Since `dup` is dynamically allocated, it has
	// to be freed to avoid memory leak (see `strdup(3)`). But `strsep(3)` will
	// modify it, thus create `end` for `strsep(3)` while keep `dup` for
	// `free(3)`.
	char *dup = strdup(str);
	errorf(dup, "malloc failed");

	char *end = dup;
	struct pair_t pair;
	memset(&pair, 0, sizeof(struct pair_t));

	char *key	= strsep(&end, ",");
	char *value = strsep(&end, ",");

	if (!key && !value)
	{
		fprintf(stderr, "cannot parse line");
		exit(EXIT_FAILURE);
	}

	pair.key = strdup(key);
	errorf(pair.key, "malloc failed");

	pair.val = strdup(value);
	errorf(pair.val, "malloc failed");

	free(dup);
	return pair;
}

void
freepair(struct pair_t pair)
{
	free(pair.key);
	free(pair.val);
}

struct kvs_t *
init_htable()
{
	struct kvs_t *htable = (struct kvs_t *)malloc(sizeof(struct kvs_t));

	if (htable == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	errorf(htable, "malloc failed");

	htable->cap = INIT_CAP;
	htable->cnt = 0;
	htable->chains =
		(struct list_t **)malloc(sizeof(struct list_t *) * htable->cap);

	for (size_t i = 0; i < htable->cap; i++)
		htable->chains[i] = NULL;

	errorf(htable->chains, "malloc failed");

	return htable;
}

void
free_list(struct node_t *begin)
{
	struct node_t *curr;

	while (begin != NULL)
	{
		curr  = begin;
		begin = begin->next;

		freepair(curr->val);
		free(curr);
	}
}

void
free_htable(struct kvs_t *htable)
{
	if (htable == NULL)
		return;

	for (size_t i = 0; i < htable->cap; ++i)
	{
		struct list_t *list = htable->chains[i];

		if (list == NULL)
			continue;

		struct node_t *first = list->first;
		free_list(first);
		free(list);
	}

	free(htable->chains);
}
