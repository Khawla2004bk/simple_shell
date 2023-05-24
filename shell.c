#include "shell.h"

/**
 * main - Entry point
 * @ac: number of values received
 * @av: values received from the cmd
 * @envt: number of values
 * Return: 0 on succes
 */
int main(int ac, char *av[], char *envt[])
{
	datas info_struct = {NULL}, *info = &info_struct;
	char *p = "";

	datainit(info, ac, av, envt);
	signal(SIGINT, ctrl_c);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1)
	{
		errno = 2;
		p = "$";
	}
	errno = 0;
	prpt(p, info);
	return (0);
}

/**
 * ctrl_c - print the prompt
 * @UNUSED: option
 */
void ctrl_c(int op UNUSED)
{
	_print("\n");
	_print("$");
}

/**
 * datainit - inicialize the struct
 * @info: pointer to structure of data
 * @av: array of arguments
 * @envt: environ pased to the program
 * @ac: number of values received
 */
void datainit(datas *info, int ac, char **av, char **envt)
{
	int j = 0;

	info->progname = av[0];
	info->linput = NULL;
	info->namecmd = NULL;
	info->countexec = 0;
	if (ac == 1)
		info->filedesc = STDIN_FILENO;
	else
	{
		info->file_desc = open(av[1], O_RDONLY);
		if (info->file_desc == -1)
		{
			print(info->progname);
			print(": 0: Can't open ");
			print(av[1]);
			print("\n");
			exit(127);
		}
	}
	info->tok = NULL;
	info->envt = malloc(sizeof(char *) * 50);
	if (envt)
	{
		for (; envt[j]; j++)
			info->envt[j] = str_dup(envt[j]);
	}
	info->envt[j] = NULL;
	envt = info->envt;
	info->aliasl = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
		info->aliasl[j] = NULL;
}

/**
 * Prompt - infinite loop shows the prompt
 * @p: prompt
 * @info: infinite loop that shows the prompt
 */
void Prompt(char *p, datas *info)
{
	int error = 0, len = 0;

	while (++(info->countexec))
	{
		__print(p);
		error = len = mgetline(info);
		if (error == EOF)
		{
			free_all(info);
			exit(errno);
		}
		if (len >= 1)
		{
			expandals(info);
			expandvar(info);
			token(info);
			if (info->tok[0])
			{
				error = execute(info);
				if (error != 0)
					print_error(error, info);
			}
			recurdata_free(info);
		}
	}
}
