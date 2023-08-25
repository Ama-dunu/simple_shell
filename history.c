#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: parameter struct.
 * Return: allocated string containing history file path.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	/* Get the user's home directory */
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	/* Allocate memory for the history file path */
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0; /* Initialize the buffer with an empty string */
	_strcpy(buf, dir); /* Copy the home directory path to the buffer */
	_strcat(buf, "/"); /* Concatenate a directory separator */
	_strcat(buf, HIST_FILE); /* Concatenate the history file name */

	return (buf); /* Return the history file path */
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info); /* Get the history file path */
	list_t *node = NULL;

	if (!filename)
		return (-1);

	/* Open the history file for writing, creating if not exist, truncating if exist */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename); /* Free the allocated filename memory */
	if (fd == -1)
		return (-1); /* Return -1 on failure */

	/* Loop through the history list and write each entry to the history file */
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd); /* Write the history entry string */
		_putfd('\n', fd); /* Write a newline character after each entry */
	}

	_putfd(BUF_FLUSH, fd); /* Flush any buffered data to the file */
	close(fd); /* Close the history file */
	return (1); /* Return 1 on success */
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return (0);

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		return (free(buf), 0);

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	// Traverse the history linked list and update the 'num' field
	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	// Update the histcount to the new value
	return (info->histcount = i);
}

