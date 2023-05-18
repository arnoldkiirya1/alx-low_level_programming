#include "lists.h"

/**
 * sum_dlistint - function that returns the sum of all the,
 * data (n) of a linked list.
 * @head: pointer to pointer to head of linked list.
 *
 * If the list is empty, return 0.
 *
 * Return: The sum.
 */

int sum_dlistint(dlistint_t *head)
{
    int sum = 0;
    
    dlistint_t *current = head;

    while (current != NULL)
    {
        sum += current->n;
        current = current->next;
    }

    return sum;
}
