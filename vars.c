#include "shell.h"

/**
 * is_chain - Checks if the current character in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
char current_char = buf[j];

if (current_char == '|' && buf[j + 1] == '|')
{
buf[j] = '\0'; /* Replace with null terminator
j++; /* Move to the next character
info->cmd_buf_type = CMD_OR;
}
else if (current_char == '&' && buf[j + 1] == '&')
{
buf[j] = '\0';
j++;
info->cmd_buf_type = CMD_AND;
}
else if (current_char == ';')
{
buf[j] = '\0';
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}

*p = j;
return (1);
}

/**
 * check_chain - Determines whether to continue chaining based on the last status.
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
size_t j = *p;


if (info->cmd_buf_type == CMD_AND && info->status)
{
buf[i] = '\0';
j = len;
}
else if (info->cmd_buf_type == CMD_OR && !info->status)
{
buf[i] = '\0';
j = len;
}

*p = j;
}

/**
 * replace_alias - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
int i;
list_t *node;
char *alias_value;

for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return 0;

free(info->argv[0]);
alias_value = _strchr(node->str, '=') + 1;
info->argv[0] = _strdup(alias_value);
if (!info->argv[0])
return 0;
}
 
return 1;
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: Always returns 0.
 */
int replace_vars(info_t *info)
{
for (int i = 0; info->argv[i]; i++)
{
char *current_arg = info->argv[i];

if (current_arg[0] == '$' && current_arg[1])
{
if (!_strcmp(current_arg, "$?"))
{
replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
}
else if (!_strcmp(current_arg, "$$"))
{
replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
}
else
{
list_t *node = node_starts_with(info->env, &current_arg[1], '=');
if (node)
{
char *env_value = _strchr(node->str, '=') + 1;
replace_string(&(info->argv[i]), _strdup(env_value));
}
else
{
replace_string(&info->argv[i], _strdup(""));
}
}
}
}
return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: Always returns 1.
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
