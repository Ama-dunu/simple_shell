 #include "shell.h"

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!d)
		d = " ";

	/* Count the number of words */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the string into words and store in the array */
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		/* Allocate memory for the word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy the word into the array */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL; /* Mark the end of the array with a NULL pointer */
	return (s);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	/* Count the number of words */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the string into words and store in the array */
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != '\0')
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		/* Allocate memory for the word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy the word into the array */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}
	s[j] = NULL; /* Mark the end of the array with a NULL pointer */
	return (s);
}

