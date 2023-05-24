#include "shell.h"

/**
 * mgetline - read line from the prompt
 * @info: struct for the program's info
 * Return: reading counting bytes
 */
int mgetline(datas *info)
{
	char buf[BUFFER_SIZE] = {'\0'};
	static char *cmds[10] = {NULL};
	static char oprs[10] = {'\0'};
	ssize_t bytes, x = 0;

	if (!cmds[0] || (oprs[0] == '&' && errno != 0) ||
		(oprs[0] == '|' && errno == 0))
	{
		for (x = 0; cmds[x]; x++)
		{
			free(cmds[x]);
			cmds[x] = NULL;
		}
		bytes = read(info->filedesc, &buf, BUFFER_SIZE - 1);
		if (bytes == 0)
			return (-1);
		x = 0;
		do {
			cmds[x] = str_dup(str_tok(x ? NULL : buf, "\n;"));
			x = logic_ops(cmds, x, oprs);
		} while (cmds[x++]);
	}
	info->linput = cmds[0];
	for (x = 0; cmds[x]; x++)
	{
		cmds[x] = cmds[x + 1];
		oprs[x] = oprs[x + 1];
	}
	return (str_len(info->linput));
}

/**
 * logic_ops - checks and split for && and ||
 * @cmds: array of the comd
 * @x: index to be checked
 * @oprs: array of the logical operators
 * Return: index of the last command
 */
int logic_ops(char *cmds[], int x, char oprs[])
{
	char *tmp = NULL;
	int i;

	for (i = 0; cmds[x] != NULL  && cmds[x][i]; i++)
	{
		if (cmds[x][i] == '&' && cmds[x][i + 1] == '&')
		{
			tmp = cmds[x];
			cmds[x][i] = '\0';
			cmds[x] = str_dup(cmds[x]);
			cmds[x + 1] = str_dup(tmp + i + 2);
			x++;
			oprs[x] = '&';
			free(tmp);
			i = 0;
		}
		if (cmds[x][i] == '|' && cmds[x][i + 1] == '|')
		{
			tmp = cmds[x];
			cmds[x][i] = '\0';
			cmds[x] = str_dup(cmds[x]);
			cmds[x + 1] = str_dup(tmp + i + 2);
			x++;
			oprs[x] = '|';
			free(tmp);
			i = 0;
		}
	}
	return (x);
}
