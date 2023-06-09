#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * hash_table_create - Creates a hash table
 * @size: The size of the array
 *
 * Return: A pointer to the newly created hash table, or NULL if it fails
 */
hash_table_t *hash_table_create(unsigned long int size)
{
    hash_table_t *hash_table = NULL;
    unsigned long int i = 0;

    hash_table = malloc(sizeof(hash_table_t));
    if (hash_table == NULL)
        return (NULL);

    hash_table->size = size;

    hash_table->array = malloc(sizeof(hash_node_t *) * size);
    if (hash_table->array == NULL)
    {
        free(hash_table);
        return (NULL);
    }

    for (i = 0; i < size; i++)
        hash_table->array[i] = NULL;

    return (hash_table);
}

/**
 * hash_djb2 - Hash function using the djb2 algorithm
 * @str: The string to hash
 *
 * Return: The hash value
 */
unsigned long int hash_djb2(const unsigned char *str)
{
    unsigned long int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash);
}

/**
 * key_index - Get the index of a key
 * @key: The key
 * @size: The size of the array of the hash table
 *
 * Return: The index of the key
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    return (hash_djb2(key) % size);
}

/**
 * hash_table_set - Adds an element to the hash table
 * @ht: The hash table
 * @key: The key
 * @value: The value corresponding to the key
 *
 * Return: 1 if successful, 0 otherwise
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    unsigned long int index = 0;
    hash_node_t *new_node = NULL, *tmp = NULL;

    if (ht == NULL || key == NULL || value == NULL)
        return (0);

    index = key_index((unsigned char *)key, ht->size);
    tmp = ht->array[index];
    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            return (1);
        }
        tmp = tmp->next;
    }

    new_node = malloc(sizeof(hash_node_t));
    if (new_node == NULL)
        return (0);

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    return (1);
}

/**
 * hash_table_get - Retrieves a value associated with a key in the hash table
 * @ht: The hash table
 * @key: The key
 *
 * Return: The value associated with the key, or NULL if the key is not found
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
    unsigned long int index = 0;
    hash_node_t *tmp = NULL;

    if (ht == NULL || key == NULL)
        return (NULL);

    index = key_index((unsigned char *)key, ht->size);
    tmp = ht->array[index];

    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }

    return (NULL);
}

/**
 * hash_table_print - Prints the hash table
 * @ht: The hash table
 */
void hash_table_print(const hash_table_t *ht)
{
    unsigned long int i = 0;
    hash_node_t *node = NULL;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");
    for (i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            if (!first)
                printf(", ");
            printf("'%s': '%s'", node->key, node->value);
            first = 0;
            node = node->next;
        }
    }
    printf("}\n");
}

/**
 * hash_table_delete - Deletes a hash table
 * @ht: The hash table
 */
void hash_table_delete(hash_table_t *ht)
{
    unsigned long int i = 0;
    hash_node_t *node = NULL, *tmp = NULL;

    if (ht == NULL)
        return;

    for (i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }

    free(ht->array);
    free(ht);
}
