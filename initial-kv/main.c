/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 */

#include "kvs.h"
#include <string.h>

int
main()
{
	FILE *fp = fopen("database.txt", "r");

	struct kvs_t *kvs = init_htable();

	char *buffer = NULL;
	size_t nread = 0;
	while (getline(&buffer, &nread, fp) != -1)
	{
		struct pair_t pair = parsepair(buffer);

		put(kvs, pair);
	}

	fclose(fp);

	fp = fopen("database.txt", "w");
	save(fp, kvs);

	free_htable(kvs);
	free(kvs);
	free(buffer);
	fclose(fp);

	return 0;
}
