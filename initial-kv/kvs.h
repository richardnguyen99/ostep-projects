#ifndef __KVS_H
#define __KVS_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define INIT_HASH_VALUE 5381
#define INIT_CAP 64
#define LOAD_FACTOR 0.75

	struct pair_t
	{
		void *key;
		void *val;
	};

	struct node_t
	{
		struct pair_t val;
		struct node_t *next;
	};

	struct list_t
	{
		struct node_t *first;
		struct node_t *last;
	};

	struct kvs_t
	{
		struct list_t **chains;
		size_t cnt;
		size_t cap;
	};

	struct pair_t
	parsepair(const char *str);

	void
	freepair(struct pair_t pair);

	struct kvs_t *
	init_htable();

	void
	free_htable(struct kvs_t *htable);

	int
	put(struct kvs_t *htable, struct pair_t pair);

	char *
	get(struct kvs_t *htable, void *key);

	void
	update(struct kvs_t *htable, void *key, void *new_value);

	int
	destroy(struct kvs_t *htable, void *key);

	void
	save(FILE *stream, struct kvs_t *htable);

#ifdef __cplusplus
}
#endif

#endif // __KVS_H
