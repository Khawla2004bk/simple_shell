#include "shell.h"

/**
 * sig_handl - inspects the Ctrl C button
 * @sig: integer
 */
void sig_handl(int sig)
{
	if (sig == SIGINT)
		__puts("\n#cisfun$ ");
}

/**
 * __EOF - the End of File handler
 * @l: return value of getline
 * @buf: buffer.
 */
void __EOF(int l, char *buf)
{
	(void)buf;
	if (l == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			__puts("\n");
			free(buf);
		}
		exit(0);
	}
}

/**
  * __isatty - verify if terminal
  */

void __isatty(void)
{
	if (isatty(STDIN_FILENO))
		__puts("#cisfun$ ");
}

/**
 * main - Entry point
 * Return: 0
 */

int main(void)
{
	ssize_t l = 0;
	char *buf = NULL, *val, *path, **av;
	size_t siz = 0;
	pathl *h = '\0';
	void (*funct)(char **);

	signal(SIGINT, sig_handl);
	while (l != EOF)
	{
		__isatty();
		l = getline(&buf, &siz, stdin);
		__EOF(l, buf);
		av = splitstr(buf, " \n");
		if (!av || !av[0])
			_execute(av);
		else
		{
			val = __getenv("PATH");
			h = pathlink(val);
			path = __which(av[0], h);
			funct = _checkbuild(av);
			if (funct)
			{
				free(buf);
				funct(av);
			}
			else if (!path)
				_execute(av);
			else if (path)
			{
				free(av[0]);
				av[0] = path;
				_execute(av);
			}
		}
	}
	freel(h);
	freeav(av);
	free(buf);
	return (0);
}
