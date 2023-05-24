#include "shell.h"

/**
 * token - separate string using a designed delimiter
 * @info: pointer to the program's data
 * Return: array of the different parts of string
 */
void token(datas *info)
{
	char *del = " \t";
	int x, y, count = 2, len;

	len = str_len(info->linput);
	if (len)
	{
		if (info->linput[len - 1] == '\n')
			info->linput[len - 1] = '\0';
	}
	for (x = 0; info->linput[y]; x++)
	{
		for (y = 0; del[y]; y++)
		{
			if (info->linput[x] == del[y])
				count++;
		}
	}
	info->tok = malloc(count * sizeof(char *));
	if (info->tok == NULL)
	{
		perror(info->progname);
		exit(errno);
	}
	x = 0;
	info->tok[x] = str_dup(str_tok(info->linput, del));
	info->namecmd = str_dup(info->tok[0]);
	while (info->tok[x++])
		info->tok[x] = str_dup(str_tok(NULL, del));
}
