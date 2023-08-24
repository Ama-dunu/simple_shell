#include "shell.h"

/**
 * add_node - Adds a node to the beginning of the linked list.
 * @head: Address of pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index of the node used for history.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
if (!head)
return (NULL);

list_t *new_node = malloc(sizeof(list_t));
if (!new_node)
	return (NULL);

_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;

if (str)
{
	new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

new_node->next = *head;
*head = new_node;
return (new_node);
}

/**
 * add_node_end - Adds a node to the end of the linked list.
 * @head: Address of pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index of the node used for history.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
if (!head)
return (NULL);

list_t *new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);

_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;

if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

new_node->next = NULL;

if (*head)
{
list_t *node = *head;
while (node->next)
node = node->next;
node->next = new_node;
}
else
{
*head = new_node;
}

return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
size_t count = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
count++;
}

return (count);
}

/**
 * delete_node_at_index - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
if (!head || !*head)
return (0);

list_t *node = *head;
list_t *prev_node = NULL;
unsigned int i = 0;

if (index == 0)
{
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}

while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}

return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
if (!head_ptr || !*head_ptr)
return;

list_t *node = *head_ptr;
while (node)
{
list_t *next_node = node->next;
free(node->str);
free(node);
node = next_node;
}

*head_ptr = NULL;
}

