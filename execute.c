#include "shell.h"

/**
 * execute - execute a command
 * @info: a pointer to the program's info
 * Return: If sucess returns 0, otherwise, return -1.
 */
int execute(datas *info)
{
	int val = 0, status;
	pid_t cpid;

	val = builtinl(info);
	if (val != -1)
		return (val);

	val = progfind(info);
	if (val)
		return (val);

	else
	{
		cpid = fork();
		if (cpid == -1)
		{
			perror(info->namecmd);
			exit(EXIT_FAILURE);
		}
		if (cpid == 0)
		{
			val = execve(info->tok[0], info->tok,
					info->envt);
			if (val == -1)
				perror(info->namecmd);
					exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
