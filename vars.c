#include "shell.h"

/**
 * is_chain - Tests if the current character in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0; /* Replace '||' with null terminator */
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0; /* Replace '&&' with null terminator */
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* Found end of this command */
	{
		buf[j] = 0; /* Replace semicolon with null terminator */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	/* Initialize variables */
	size_t j = *p;

	/* If the previous command was successful and the current delimiter is && */
	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = '\0';
		j = len; /* Skip remaining characters in buffer */
	}

	/* If the previous command was not successful and the current delimiter is || */
	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = '\0';
		j = len; /* Skip remaining characters in buffer */
	}

	/* Update the current position pointer */
	*p = j;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	/* Initialize variables */
	int i;
	list_t *node;
	char *p;

	/* Iterate through a limited number of replacements */
	for (i = 0; i < 10; i++)
	{
		/* Find an alias that matches the current command */
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		/* Free the current command and update it with the alias value */
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	/* Iterate through each argument */
	for (i = 0; info->argv[i]; i++)
	{
		/* Check if the argument starts with '$' */
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		/* Replace special variables */
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		/* Replace environment variables */
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		/* Replace with an empty string if no match found */
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);   /* Free the memory of the old string */
	*old = new;   /* Assign the new string */
	return (1);
}

