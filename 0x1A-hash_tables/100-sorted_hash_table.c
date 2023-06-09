#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the newly created sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht;
    unsigned long int i;

    ht = malloc(sizeof(shash_table_t));
    if (ht == NULL)
        return NULL;

    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL)
    {
        free(ht);
        return NULL;
    }

    for (i = 0; i < size; i++)
        ht->array[i] = NULL;

    ht->shead = NULL;
    ht->stail = NULL;

    return ht;
}

/**
 * shash_table_set - Sets a key/value pair in the sorted hash table
 * @ht: The sorted hash table
 * @key: The key string
 * @value: The value string
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    shash_node_t *node, *prev, *new_node;
    unsigned long int index;

    if (ht == NULL || key == NULL || value == NULL)
        return 0;

    index = key_index((unsigned char *)key, ht->size);
    node = ht->array[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            free(node->value);
            node->value = strdup(value);
            return 1;
        }
        node = node->next;
    }

    new_node = malloc(sizeof(shash_node_t));
    if (new_node == NULL)
        return 0;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->array[index];

    if (ht->array[index] != NULL)
        ht->array[index]->sprev = new_node;

    ht->array[index] = new_node;

    /* Update sorted linked list */
    prev = NULL;
    node = ht->shead;

    while (node != NULL && strcmp(key, node->key) > 0)
    {
        prev = node;
        node = node->snext;
    }

    new_node->sprev = prev;
    new_node->snext = node;

    if (prev != NULL)
        prev->snext = new_node;
    else
        ht->shead = new_node;

    if (node != NULL)
        node->sprev = new_node;
    else
        ht->stail = new_node;

    return 1;
}

/**
 * shash_table_get - Retrieves a value associated with a key from the sorted hash table
 * @ht: The sorted hash table
 * @key: The key string
 *
 * Return: The value associated with the key, or NULL if the key is not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
    shash_node_t *node;
    unsigned long int index;

    if (ht == NULL || key == NULL)
        return NULL;

    index = key_index((unsigned char *)key, ht->size);
    node = ht->array[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;

        node = node->next;
    }

    return NULL;
}

/**
 * shash_table_print - Prints the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");

    node = ht->shead;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->snext;
    }

    printf("}\n");
}

/**
 * shash_table_print_rev - Prints the sorted hash table in reverse order
 * @ht: The sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");

    node = ht->stail;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->sprev;
    }

    printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
    shash_node_t *node, *temp;
    unsigned long int i;

    if (ht == NULL)
        return;

    for (i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(ht->array);
    free(ht);
}
