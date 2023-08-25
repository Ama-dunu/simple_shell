#include "shell.h"

/**
 * custom_exit - Exits the shell
 * @custom_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Exits with a given exit status (0) if custom_info->argv[0] != "exit"
 */
int custom_exit(info_t *custom_info)
{
	int exit_check;

	if (custom_info->argv[1]) /* If there is an exit argument */
	{
		exit_check = custom_erratoi(custom_info->argv[1]);
		if (exit_check == -1)
		{
			custom_info->status = 2;
			print_error(custom_info, "Illegal number: ");
			_custom_eputs(custom_info->argv[1]);
			_custom_eputchar('\n');
			return (1);
		}
		custom_info->err_num = custom_erratoi(custom_info->argv[1]);
		return (-2);
	}
	custom_info->err_num = -1;
	return (-2);
}

/**
 * custom_mycd - Changes the current directory of the process
 * @custom_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int custom_mycd(info_t *custom_info)
{
	char *custom_str, *custom_dir, custom_buffer[1024];
	int custom_chdir_ret;

	custom_str = getcwd(custom_buffer, 1024);
	if (!custom_str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!custom_info->argv[1])
	{
		custom_dir = custom_getenv(custom_info, "HOME=");
		if (!custom_dir)
			custom_chdir_ret =
				chdir((custom_dir = custom_getenv(custom_info, "PWD=")) ? custom_dir : "/");
		else
			custom_chdir_ret = chdir(custom_dir);
	}
	else if (_custom_strcmp(custom_info->argv[1], "-") == 0)
	{
		if (!custom_getenv(custom_info, "OLDPWD="))
		{
			_puts(custom_str);
			_putchar('\n');
			return (1);
		}
		_puts(custom_getenv(custom_info, "OLDPWD=")), _putchar('\n');
		custom_chdir_ret =
			chdir((custom_dir = custom_getenv(custom_info, "OLDPWD=")) ? custom_dir : "/");
	}
	else
		custom_chdir_ret = chdir(custom_info->argv[1]);
	if (custom_chdir_ret == -1)
	{
		print_error(custom_info, "can't cd to ");
		_custom_eputs(custom_info->argv[1]), _custom_eputchar('\n');
	}
	else
	{
		_custom_setenv(custom_info, "OLDPWD", custom_getenv(custom_info, "PWD="));
		_custom_setenv(custom_info, "PWD", getcwd(custom_buffer, 1024));
	}
	return (0);
}

/**
 * custom_myhelp - Displays help information (not yet implemented)
 * @custom_info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int custom_myhelp(info_t *custom_info)
{
	char **custom_arg_array;

	custom_arg_array = custom_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*custom_arg_array); /* Temp unused attribute workaround */
	return (0);
}

