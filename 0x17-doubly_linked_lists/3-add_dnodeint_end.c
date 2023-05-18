#include "lists.h"

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

