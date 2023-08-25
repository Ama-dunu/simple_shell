#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new head of the list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head) /* Check if head pointer is valid */
		return (NULL);

	/* Allocate memory for the new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	/* Initialize the new node */
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	/* Duplicate the input string if provided */
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	/* Update the new node's next pointer and the head of the list */
	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node added at the end
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head) /* Check if head pointer is valid */
		return (NULL);

	/* Initialize new_node and node pointers */
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	/* Initialize the new node */
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	/* Duplicate the input string if provided */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node) /* If the list is not empty */
	{
		/* Traverse to the last node */
		while (node->next)
			node = node->next;
		/* Append new_node at the end */
		node->next = new_node;
	}
	else /* If the list is empty */
		*head = new_node; /* Update head to point to the new node */

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: number of nodes in the list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		/* Print the str element or "(nil)" if it's NULL */
		_puts(h->str ? h->str : "(nil)");
		_puts("\n"); /* Print a newline after each element */
		h = h->next; /* Move to the next node */
		i++; /* Increment the counter for nodes */
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head) /* Check if the list is empty */
		return (0);

	if (!index) /* If the index is 0, delete the first node */
	{
		node = *head;
		*head = (*head)->next; /* Update the head pointer */
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index) /* If we've reached the desired index */
		{
			prev_node->next = node->next; /* Update previous node's next pointer */
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node; /* Keep track of the previous node */
		node = node->next; /* Move to the next node */
	}
	return (0); /* Node at the given index was not found */
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr) /* Check if the list is empty */
		return;
	head = *head_ptr; /* Store the head pointer for reference */
	node = head;
	while (node)
	{
		next_node = node->next; /* Store the next node before freeing the current one */
		free(node->str);
		free(node);
		node = next_node; /* Move to the next node */
	}
	*head_ptr = NULL; /* Set the head pointer to NULL to indicate an empty list */
}

