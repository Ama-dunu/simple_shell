#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _isalpha - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number or 0 if no numbers in the string.
 */
int _atoi(char *s)
{
	int sign = 1, flag = 0, output = 0;
	int i;

	for (i=0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (_isalpha(s[i]))
			flag = 1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			output = output * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	return (sign * output);
}

