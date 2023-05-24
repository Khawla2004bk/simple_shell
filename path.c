#include "shell.h"

/**
 * progfind - find a program
 * @info: a pointer to the program's data
 * Return: 0 if success
 */
int progfind(datas *info)
{
	int x = 0, ret = 0;
	char **dir;

	if (!info->namecmd)
		return (2);
	if (info->namecmd[0] == '/' || info->namecmd[0] == '.')
		return (checkfile(info->namecmd));
	free(info->tok[0]);
	info->tok[0] = concat_str(str_dup("/"), info->namecmd);
	if (!info->tok[0])
		return (2);
	dir = pathtoken(info);
	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; dir[x]; x++)
	{
		dir[x] = concat_str(dir[x], info->tok[0]);
		ret = checkfile(dir[x]);
		if (ret == 0 || ret == 126)
		{
			errno = 0;
			free(info->tok[0]);
			info->tok[0] = str_dup(dir[x]);
			freearr(dir);
			return (ret);
		}
	}
	free(info->tok[0]);
	info->tok[0] = NULL;
	freearr(dir);
	return (ret);
}

/**
 * pathtoken - tokenize path in directories
 * @info: pointer to the program's data
 * Return: array of path directories
 */
char **pathtoken(datas *info)
{
	int x = 0;
	int count = 2;
	char **token = NULL;
	char *P;

	P = get_key("PATH", info);
	if ((P == NULL) || P[0] == '\0')
		return (NULL);
	P = str_dup(P);

	for (x = 0; P[x]; x++)
		if (P[x] == ':')
			count++;

	token = malloc(sizeof(char *) * count);

	x = 0;
	token[x] = str_dup(str_tok(P, ":"));
	while (token[x++])
		token[x] = str_dup(str_tok(NULL, ":"));
	free(P);
	P = NULL;
	return (token);
}

/**
 * checkfile - checks if exists
 * @full: pointer to full file name
 * Return: 0 on success, or error code
 */
int checkfile(char *full)
{
	struct stat st;

	if (stat(full, &st) != -1)
	{
		if (S_ISDIR(st.st_mode) ||  access(full, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
