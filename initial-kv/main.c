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
main(int argc, const char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		struct pair_t *pair = parsepair(argv[i]);

		printf("\
{\n\
    key: %s,\n\
    value: %s \n\
}\n",
			   (char *)(pair->key), (char *)(pair->val));
		freepair(pair);
	}

	return 0;
}
