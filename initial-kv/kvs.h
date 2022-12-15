#ifndef __KVS_H
#define __KVS_H 1

#include <stddef.h>
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

	struct kvs_t
	{
		struct pair_t *pairs;
		size_t cnt;
		size_t cap;
	};

	struct pair_t *
	parsepair(const char *str);

	void
	freepair(struct pair_t *pair);

#ifdef __cplusplus
}
#endif

#endif // __KVS_H
