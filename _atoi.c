#include "shell.h"

/**
 * interactive - Returns true if the shell is in interactive mode.
 * @info: Pointer to a structure containing shell information.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @ch: The character to check.
 * @delim_str: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */

int is_delim(char ch, char *delim_str)
{
	while (*delim_str)
		if (*delim_str++ == ch)
			return (1);
	return (0);
}

/**
 * _is_alpha - Checks if a character is an alphabetic character.
 * @ch: The character to check.
 *
 * Return: 1 if ch is alphabetic, 0 otherwise.
 */

int _is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in string, otherwise the converted number.
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

