#include "shell.h"

/**
 * __print - writes array of chars
 * @str: pointer to the array
 * Return: the number of bytes, On error -1 and errno is set appropriately
 */
int __print(char *str)
{
	return (write(STDOUT_FILENO, str, str_len(str)));
}

/**
 * print_error - writes array of chars
 * @info: ...
 * @error: error code
 * Return: ...
 */
int print_error(int error, datas *info)
{
	char n[10] = {'\0'};

	int_str((long) info->countexec, n, 10);
	if (error == 2 || error == 3)
	{
		__print(info->progname);
		__print(": ");
		__print(n);
		__print(": ");
		__print(info->tok[0]);
		if (error == 2)
			__print(": illegal number: ");
		else
			__print(": Can't cd to ");
		__print(info->tok[1]);
		__print("\n");
	}
	else if (error == 127)
	{
		__print(info->progname);
		__print(": ");
		__print(n);
		__print(": ");
		__print(info->namecmd);
		__print(": Not found\n");
	}
	else if (error == 126)
	{
		__print(info->progname);
		__print(": ");
		__print(n);
		__print(": ");
		__print(info->namecmd);
		__print(": Permission Denied\n");
	}
	return (0);
}
