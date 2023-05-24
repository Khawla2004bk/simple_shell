#include "shell.h"

/**
 * builtinl - search for match and execute builtin
 * @info: ...
 * Return: ...
 **/
int builtinl(datas *info)
{
	int iter;
	builtin_s opts[] = {
		{"exit", exiit},
		{"help", _help},
		{"cd", _cd},
		{"alias", _alias},
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
	for (iter = 0; opts[iter].built != NULL; iter++)
	{
		if (str_cmp(opts[iter].built, info->namecmd, 0))
			return (opts[iter].funct(info));
	}
	return (-1);
}
