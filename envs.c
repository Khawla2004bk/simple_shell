#include "shell.h"

/**
 * _env - shows the environment where shell runs
 * @info: struct for the program's info
 * Return: 0 if sucess, or other number if its declared
 */
int _env(datas *info)
{
	int x;
	char cp[50] = {'\0'};
	char *copy = NULL;

	if (info->tok[1] == NULL)
		printenv(info);
	else
	{
		for (x = 0; info->tok[1][x]; x++)
		{
			if (info->token[1][x] == '=')
			{
				copy = str_dup(get_key(cp, info));
				if (copy != NULL)
					set_key(cp, info->tok[1] + x + 1, info);
				printenv(info);
				if (get_key(cp, info) == NULL)
				{
					__print(info->tok[1]);
					__print("\n");
				}
				else
				{
					set_key(cp, copy, info);
					free(copy);
				}
				return (0);
			}
			cp[x] = info->tok[1][x];
		}
		errno = 2;
		perror(info->namecmd);
		errno = 127;
	}
	return (0);
}

/**
 * set_env - ...
 * @info: struct for the program's info
 * Return: 0 if sucess, or other number if its declared
 */
int set_env(datas *info)
{
	if (info->tok[1] == NULL || info->tok[2] == NULL)
		return (0);
	if (info->tok[3] != NULL)
	{
		errno = E2BIG;
		perror(info->namecmd);
		return (5);
	}
	set_key(info->tok[1], info->tok[2], info);
	return (0);
}

/**
 * unset_env - ...
 * @info: ...
 * Return: ...
 */
int unset_env(datas *info)
{
	if (info->tok[1] == NULL)
		return (0);
	if (info->tok[2] != NULL)
	{
		errno = E2BIG;
		perror(info->namecmd);
		return (5);
	}
	remove_key(info->tok[1], info);

	return (0);
}
