#include "shell.h"

/**
 * custom_interactive - Determines if the shell is in interactive mode.
 * @custom_info: Pointer to custom struct containing shell information.
 *
 * Return: 1 if interactive mode, 0 otherwise.
 */
int custom_interactive(custom_info_t *custom_info)
{
	return (isatty(STDIN_FILENO) && custom_info->custom_readfd <= 2);
}

/**
 * custom_is_delim - Checks if a character is a custom delimiter.
 * @ch: The character to check.
 * @delim_str: The delimiter string.
 *
 * Return: 1 if character is a delimiter, 0 otherwise.
 */
int custom_is_delim(char ch, char *delim_str)
{
	while (*delim_str)
	{
		if (*delim_str++ == ch)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * custom_is_alpha - Checks if a character is alphabetic.
 * @ch: The character to check.
 *
 * Return: 1 if ch is alphabetic, 0 otherwise.
 */
int custom_is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * custom_atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 */
int custom_atoi(char *str)
{
	int i, custom_sign = 1, custom_flag = 0, output;
	unsigned int custom_result = 0;

	for (i = 0; str[i] != '\0' && custom_flag != 2; i++)
	{
		if (str[i] == '-')
		{
			custom_sign *= -1;
		}

		if (str[i] >= '0' && str[i] <= '9')
		{
			custom_flag = 1;
			custom_result *= 10;
			custom_result += (str[i] - '0');
		}
		else if (custom_flag == 1)
		{
			custom_flag = 2;
		}
	}

	if (custom_sign == -1)
	{
		output = -custom_result;
	}
	else
	{
		output = custom_result;
	}

	return (output);
}

