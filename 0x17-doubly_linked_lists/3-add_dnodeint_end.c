#include "lists.h"

/**
 * add_dnodeint_end - function that adds node at the end of a list.
 * @head: pointer to pointer to head of list.
 * @n: data to be added.
 *
 * Return: address of the new element or NULL if it failed.
 */

dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
    dlistint_t *new_node = malloc(sizeof(dlistint_t));
    if (new_node == NULL)
    {
        /* Return NULL if malloc fails */
        return NULL;
    }

    new_node->n = n;
    new_node->next = NULL;

    if (*head == NULL)
    {
        /* If the list is empty, make the new node the head */
        new_node->prev = NULL;
        *head = new_node;
    }
    else
    {
        dlistint_t *current = *head;

        /* Traverse to the end of the list */
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
        new_node->prev = current;
    }

    return new_node;
}
