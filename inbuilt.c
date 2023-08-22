#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if shell_info->argv[0] != "exit".
 */
int exit_shell(shell_info_t *shell_info)
{
	int exit_status;

	if (shell_info->argv[1]) /* Check for exit argument */
	{
		exit_status = _err_atoi(shell_info->argv[1]);
		if (exit_status == -1)
		{
			shell_info->status = 2;
			print_error(shell_info, "Illegal number: ");
			_e_puts(shell_info->argv[1]);
			_e_putchar('\n');
			return (1);
		}
		shell_info->err_num = _err_atoi(shell_info->argv[1]);
		return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Changes the current directory of the process.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int change_directory(shell_info_t *shell_info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!shell_info->argv[1])
	{
		target_dir = _get_env(shell_info, "HOME=");
		if (!target_dir)
			chdir_result = /* TODO: What should this be? */
				chdir((target_dir = _get_env(shell_info, "PWD=")) ? target_dir : "/")
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(shell_info->argv[1], "-") == 0)
	{
		if (!_get_env(shell_info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(shell_info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: What should this be? */
			chdir((target_dir = _get_env(shell_info, "OLDPWD=")) ? target_dir : "/");
		else
		{
			chdir_result = chdir(shell_info->argv[1]);
		}

		if (chdir_result == -1)
		{
			print_error(shell_info, "can't cd to ");
			_e_puts(shell_info->argv[1]), _e_putchar('\n');
		}
		else
		{
			_set_env(shell_info, "OLDPWD", _get_env(shell_info, "PWD="));
			_set_env(shell_info, "PWD", getcwd(buffer, 1024));
		}
		return (0);
}

/**
 * display_help - Displays help information.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_help(shell_info_t *shell_info)
{
	char **args;

	args = shell_info->argv;
	_puts("Help call works. Function not yet implemented.\n");
	if (0)
		_puts(*args); /* Temporary attribute_unused workaround */
	return (0);
}

