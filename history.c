#include "shell.h"

/**
 * get_history_file - Retrieves the history file path.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
	char *path, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!path)
		return (NULL);

	path[0] = 0;
	_strcpy(path, home_dir);
	_strcat(path, "/");
	_strcat(path, HIST_FILE);
	return (path);
}

/**
 * write_history - Creates or appends to the history file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *file_name = get_history_file(info);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history entries from the file.
 * @info: Parameter struct.
 *
 * Return: Number of history entries on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, rd_len, file_size = 0;
	struct stat st;
	char *buf = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		file_size = st.st_size;

	if (file_size < 2)
		return (0);

	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);

	rd_len = read(fd, buf, file_size);
	buf[file_size] = 0;

	if (rd_len <= 0)
		return (free(buf), 0);

	close(fd);

	for (i = 0; i < file_size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buf + last, line_count++);

	free(buf);
	info->histcount = line_count;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: Buffer containing history entry.
 * @line_count: Line count of history entry.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new history count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
