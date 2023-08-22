#include "shell.h"

/**
 * bfree - Deallocates memory and sets the pointer to NULL.
 * @ptr: Address of the pointer to deallocate.
 *
 * Return: 1 if memory was deallocated, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1); /* Memory deallocated successfully */
	}
	return (0); /* No memory to deallocate */
}

