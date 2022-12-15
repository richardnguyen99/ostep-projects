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
	char *tmp[] = {"key,31", "port,3", "key,value", "kv,store", "key,123"};

	for (int i = 0; i < 5; ++i)
	{
		struct pair_t pair = parsepair(tmp[i]);

		int res = put(kvs, pair);
		get(kvs, pair.key);

		// If there is a duplicate key, htable doesn own the memory allocated
		// for key and value strings presented in pair. Thus, it has to freed by
		// itself.
		if (res == -1)
			freepair(pair);
	}

	free_htable(kvs);
	free(kvs);

	return 0;
}
