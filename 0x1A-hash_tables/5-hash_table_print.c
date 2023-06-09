#include "hash_tables.h"
#include <stdio.h>

/**
 * hash_table_print - Prints a hash table
 * @ht: The hash table to print
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *node;
	int first_node = 1;

	if (ht == NULL)
		return;

	printf("{");
	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			if (!first_node)
				printf(", ");
			printf("'%s': '%s'", node->key, node->value);
			node = node->next;
			first_node = 0;
		}
	}
	printf("}\n");
}
