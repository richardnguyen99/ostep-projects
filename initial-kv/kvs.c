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

void
init_chain(struct kvs_t *htable, size_t idx)
{
	htable->chains[idx] = (struct list_t *)malloc(sizeof(struct list_t));
	errorf(htable->chains[idx], "malloc failed");

	struct list_t *chain = htable->chains[idx];

	chain->first = (struct node_t *)malloc(sizeof(struct node_t));
	errorf(chain->first, "malloc failed");
	chain->first->val.key = NULL;
	chain->first->val.val = NULL;
	chain->first->next	  = NULL;

	chain->last = chain->first;
}

struct node_t *
enqueue(struct list_t *chain, struct pair_t pair)
{

	struct node_t *curr = chain->first->next;
	for (; curr != NULL; curr = curr->next)
	{
		if (strcmp((char *)pair.key, (char *)(curr->val.key)) == 0)
			return curr;
	}

	struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
	errorf(node, "malloc failed");

	memcpy(&(node->val), &pair, sizeof(pair));
	node->next		  = NULL;
	chain->last->next = node;
	chain->last		  = chain->last->next;

	return node;
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

int
dequeue(struct list_t *chain, void *key)
{
	struct node_t *prev = chain->first;
	struct node_t *curr = prev->next;

	for (; curr != NULL; curr = curr->next)
	{
		if (strcmp((char *)(curr->val.key), (char *)(key)) == 0)
		{
			prev->next = curr->next;
			freepair(curr->val);
			free(curr);
			break;
		}
		prev = prev->next;
	}

	if (curr == NULL)
		return -1;

	return 0;
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

	errorf(htable->chains, "malloc failed");

	for (size_t i = 0; i < htable->cap; i++)
		htable->chains[i] = NULL;

	return htable;
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

int
put(struct kvs_t *htable, struct pair_t pair)
{
	// errorf(stream, "file steam is null");
	errorf(htable, "hash table is null");

	size_t ht_idx = hash(pair.key) % htable->cap;

	if (htable->chains[ht_idx] == NULL)
		init_chain(htable, ht_idx);

	struct node_t *res = enqueue(htable->chains[ht_idx], pair);

	if (strcmp((char *)(pair.val), (char *)(res->val.val)) != 0)
		return -1;

#ifdef DEBUG
	struct pair_t new_pair = htable->chains[ht_idx]->last->val;

	printf("Index: %ld\n", ht_idx);
	printf("\
{\n\
    key: %s,\n\
    value: %s \n\
}\n",
		   (char *)(new_pair.key), (char *)(new_pair.val));
#endif

	htable->cnt++;
	return 0;
}

int
keycmp(void *s1, void *s2)
{
	return strcmp((char *)s1, (char *)s2);
}

char *
get(struct kvs_t *htable, void *key)
{
	size_t ht_idx = hash((unsigned char *)key) % htable->cap;

	if (htable->chains[ht_idx] == NULL)
		return NULL;

	struct list_t *chain = htable->chains[ht_idx];

	struct node_t *curr = chain->first->next;
	for (; curr != NULL; curr = curr->next)
	{
		if (strcmp((char *)key, (char *)(curr->val.key)) == 0)
			break;
	}

#ifdef DEBUG
	printf("Index: %ld\n", ht_idx);
	printf("\
{\n\
    key: %s,\n\
    value: %s \n\
}\n",
		   (char *)(key), (char *)(curr->val.val));
#endif

	return (char *)(curr->val.val);
}

void
update_list(struct list_t *chain, void *key, void *new_value)
{

	struct node_t *curr = chain->first->next;
	for (; curr != NULL; curr = curr->next)
	{
		if (strcmp((char *)key, (char *)(curr->val.key)) == 0)
		{
			free(curr->val.val);
			curr->val.val = strdup(new_value);
			break;
		}
	}
}

void
update(struct kvs_t *htable, void *key, void *new_value)
{
	size_t ht_idx		 = hash((unsigned char *)key) % htable->cap;
	struct list_t *chain = htable->chains[ht_idx];

	if (chain == NULL)
	{
		struct pair_t new_pair = {key, new_value};
		enqueue(chain, new_pair);
	}
	else
		update_list(chain, key, new_value);
}

int
destroy(struct kvs_t *htable, void *key)
{
	size_t ht_idx		 = hash((unsigned char *)key) % htable->cap;
	struct list_t *chain = htable->chains[ht_idx];

	if (chain == NULL)
		return -1;

	int res = dequeue(chain, key);

	if (chain->first->next == NULL)
	{
		free_list(chain->first);
		free(htable->chains[ht_idx]);
		htable->chains[ht_idx] = NULL;
	}

	return res;
}
