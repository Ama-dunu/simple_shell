#include "shell.h"

/**
 * list_len - Returns the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts linked list elements to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t list_size = list_len(head);
	char **strs = NULL;
	char *str = NULL;
	size_t i = 0;

	if (!head || !list_size)
		return (NULL);

	strs = malloc(sizeof(char *) * (list_size + 1));
	if (!strs)
		return (NULL);

	while (head)
	{
		str = malloc(_strlen(head->str) + 1);
		if (!str)
		{
			while (i > 0)
				free(strs[--i]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, head->str);
		strs[i++] = str;
		head = head->next;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Finds a node whose string starts with the specified prefix.
 * @node: Pointer to the list head.
 * @prefix: Prefix to match.
 * @c: The next character after prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && (c == -1 || *p == c))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

