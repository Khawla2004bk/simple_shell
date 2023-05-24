#include "shell.h"

/**
 * exiit - exit of the program with status
 * @info: struct for the program's info
 * Return: ...
 */
int exiit(datas *info)
{
	int x;

	if (info->tok[1] != NULL)
	{
		for (x = 0; info->tok[1][x]; x++)
			if ((info->tok[1][x] < '0' || info->tok[1][x] > '9')
				&& info->tok[1][x] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = __atoi(info->tok[1]);
	}
	free_all(info);
	exit(errno);
}

/**
 * _cd - change the current directory
 * @info: ...
 * Return: ...
 */
int _cd(datas *info)
{
	char *home = get_key("HOME", info), *old = NULL;
	char odir[128] = {0};
	int error = 0;

	if (info->tok[1])
	{
		if (str_cmp(info->tok[1], "-", 0))
		{
			old = get_key("OLDPWD", info);
			if (old)
				error = set_dir(info, old);
			__print(get_key("PWD", info));
			__print("\n");
			return (error);
		}
		else
			return (set_dir(info, info->tok[1]));
	}
	else
	{
		if (!home)
			home = getcwd(odir, 128);
		return (set_dir(info, home));
	}
	return (0);
}

/**
 * set_dir - set work directory
 * @info: ...
 * @ndir: path to set as work directory
 * Return: ...
 */
int set_dir(datas *info, char *ndir)
{
	char odir[128] = {0};
	int err = 0;

	getcwd(odir, 128);
	if (!str_cmp(odir, ndir, 0))
	{
		err = chdir(ndir);
		if (err == -1)
		{
			errno = 2;
			return (3);
		}
		set_key("PWD", ndir, info);
	}
	set_key("OLDPWD", odir, info);
	return (0);
}

/**
 * _help - shows environment where shell runs
 * @info: ...
 * Return: ...
 */
int _help(datas *info)
{
	int x, len = 0;
	char *msj[6] = {NULL};

#define HELP "help=\n"
	msj[0] = HELP;

	if (info->tok[1] == NULL)
	{
		__print(msj[0] + 6);
		return (1);
	}
	if (info->tok[2] != NULL)
	{
		errno = E2BIG;
		perror(info->namecmd);
		return (5);
	}
#define HELP_EXIT "exit=\n"
#define HELP_ENV "env=\n"
#define HELP_SETENV "setenv=\n"
#define HELP_UNSETENV "unsetenv=\n"
#define HELP_CD "cd=\n"
	msj[1] = HELP_EXIT;
	msj[2] = HELP_ENV;
	msj[3] = HELP_SETENV;
	msj[4] = HELP_UNSETENV;
	msj[5] = HELP_CD;

	for (x = 0; msj[x]; x++)
	{
		len = str_len(info->tok[1]);
		if (str_cmp(info->tok[1], msj[x], len))
		{
			__print(msj[x] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(info->namecmd);
	return (0);
}

/**
 * _alias - add, remove or show alias
 * @info: ...
 * Return: ...
 */
int _alias(datas *info)
{
	int x = 0;

	if (info->tok[1] == NULL)
		return (printals(info, NULL));
	while (info->tok[++x])
	{
		if (char_count(info->tok[x], "="))
			set_als(info->tok[x], info);
		else
			printals(info, info->tok[x]);
	}
	return (0);
}
