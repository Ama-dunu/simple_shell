#include "shell.h"

/**
 * strtow - Splits a string into words using multiple delimiters.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	numwords = count_words(str, d);

	if (numwords == 0)
		return (NULL);
	s = malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		i = move_to_next_word(str, i, d);
		k = word_length(str, i, d);

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		copy_word(s[j], str, i, k);
		i += k;
	}
	s[j] = NULL;
	return (s);
}

/* Similar optimizations can be applied to strtow2 */

