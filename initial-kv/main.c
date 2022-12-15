/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "kvs.h"
#include <stdio.h>

int
main()
{
	struct kvs_t *kvs = init_htable();

	// For debugging
	char *tmp[] = {"key,31", "port,3", "key,value", "kv,store"};

	for (int i = 0; i < 4; ++i)
	{
		struct pair_t pair = parsepair(tmp[i]);

		put(kvs, pair);
	}

	free_htable(kvs);
	free(kvs);

	return 0;
}
