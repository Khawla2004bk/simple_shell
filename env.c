#include "shell.h"

/**
 * get_key - gets value of environment variable
 * @N: the environment variable of interest
 * @info: ...
 * Return: ...
 */
char *get_key(char *N, datas *info)
{
	int x, len = 0;

	if (NULL == N || NULL == info->envt)
		return (NULL);
	len = str_len(N);

	for (x = 0; info->envt[x]; x++)
	{
		if (str_cmp(N, info->envt[x], len)
				&& info->envt[x][len] == '=')
			return (info->envt[x] + len + 1);
	}
	return (NULL);
}

/**
 * set_key - Overwrite value of environment variable or create it
 * @k: name of the variable
 * @val: new
 * @info: ...
 * Return: ...
 */
int set_key(char *k, char *val, datas *info)
{
	int x, len = 0, nkey = 1;

	if (k == NULL || val == NULL || info->envt == NULL)
		return (1);

	len = str_len(k);
	for (x = 0; info->envt[x]; x++)
	{
		if (str_cmp(k, info->envt[x], len)
				&& info->envt[x][len] == '=')
		{
			nkey = 0;
			free(info->envt[x]);
			break;
		}
	}
	info->envt[x] = concat_str(str_dup(k), "=");
	info->envt[x] = concat_str(info->envt[x], val);
	if (nkey)
		info->envt[x + 1] = NULL;
	return (0);
}

/**
 * remove_key - remove key from environment
 * @k: key to remove
 * @info: ...
 * Return: ...
 */
int remove_key(char *k, datas *info)
{
	int x, len = 0;

	if (k == NULL || info->envt == NULL)
		return (0);
	len = str_len(k);
	for (x = 0; info->envt[x]; x++)
	{
		if (str_cmp(k, info->envt[x], len)
				&& info->envt[x][len] == '=')
		{
			free(info->envt[x]);
			x++;
			for (; info->envt[x]; x++)
				info->envt[x - 1] = info->envt[x];
			info->envt[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * printenv - prints current environ
 * @info: ...
 */
void printenv(datas *info)
{
	int i;

	for (i = 0; info->envt[i]; i++)
	{
		__print(info->envt[i]);
		__print("\n");
	}
}
