#include "shell.h"

/**
 * recurdata_free - Free fields needed each loop
 * @info: ...
 */
void recurdata_free(datas *info)
{
	if (info->tok)
		freearr(info->tok);
	if (info->linput)
		free(info->linput);
	if (info->namecmd)
		free(info->namecmd);
	info->linput = NULL;
	info->namecmd = NULL;
	info->tok = NULL;
}

/**
 * free_all - Free all field of data
 * @info: ...
 */
void free_all(datas *info)
{
	if (info->filedesc != 0)
	{
		if (close(info->filedesc))
			perror(info->progname);
	}
	recurdata_free(info);
	freearr(info->envt);
	freearr(info->aliasl);
}

/**
 * freearr - Frees pointer of array of pointers
 * @dir: array
 */
void freearr(char **dir)
{
	int x;

	if (dir != NULL)
	{
		for (x = 0; dir[x]; x++)
			free(dir[x]);
		free(dir);
		dir = NULL;
	}
}
