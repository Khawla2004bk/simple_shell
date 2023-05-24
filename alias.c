#include "shell.h"

/**
 * printals - add, remove or show aliase
 * @info: struct for the program's info
 * @als: name of the alias
 * Return: 0 if sucess, or other number if its declared
 */
int printals(datas *info, char *als)
{
	int x, y, len;
	char buf[250] = {'\0'};

	if (info->aliasl)
	{
		aliasl = str_len(als);
		for (x = 0; info->aliasl[x]; x++)
		{
			if (!als || (str_comp(info->aliasl[x], als, len)
				&& info->aliasl[x][len] == '='))
			{
				for (x = 0; info->aliasl[x][y]; y++)
				{
					buf[y] = info->aliasl[x][y];
					if (info->aliasl[x][y] == '=')
						break;
				}
				buf[y + 1] = '\0';
				addbuf(buf, "'");
				addbuf(buf, info->aliasl[x] + y + 1);
				addbuf(buf, "'\n");
				__print(buf);
			}
		}
	}
	return (0);
}

/**
 * get_als - add, remove or show aliase
 * @info: struct for program's info
 * @als: name of requested alias
 * Return: 0 if sucess, or other number if its declared
 */
char *get_als(datas *info, char *als)
{
	int x, length;

	if (als == NULL || info->aliasl == NULL)
		return (NULL);
	length = str_len(als);
	for (x = 0; info->aliasl[x]; x++)
	{
		if (str_comp(als, info->aliasl[x], length) &&
			info->aliasl[x][length] == '=')
			return (info->aliasl[x] + length + 1);
	}
	return (NULL);
}

/**
 * set_als - add, or override
 * @str: alias to be seted in form name='value'
 * @info: struct for the program's info
 * Return: 0 if sucess, or other number if its declared
 */
int set_als(char *str, datas *info)
{
	int x, y;
	char buf[250] = {'0'}, *tmp = NULL;

	if (str == NULL ||  info->aliasl == NULL)
		return (1);
	for (x = 0; str[x]; x++)
		if (str[x] != '=')
			buf[x] = str[x];
		else
		{
			tmp = get_als(info, str + x + 1);
			break;
		}
	for (y = 0; info->aliasl[y]; y++)
		if (str_comp(buf, info->aliasl[y], x)
				&& info->aliasl[y][x] == '=')
		{
			free(info->aliasl[y]);
			break;
		}
	if (tmp)
	{
		addbuf(buf, "=");
		addbuf(buf, tmp);
		info->aliasl[x] = str_dup(buf);
	}
	else
		info->aliasl[y] = str_dup(str);
	return (0);
}
