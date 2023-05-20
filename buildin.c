#include "shell.h"

/**
 * exiit - exits shell with/without return of status
 * @av: array of words
 */
void exiit(char **av)
{
	int a, b;

	if (av[1])
	{
		b = _atoi(av[1]);
		if (b <= -1)
			b = 2;
		freeav(av);
		exit(b);
	}
	for (a = 0 ; av[a] ; a++)
		free(av[a]);
	free(av);
	exit(0);
}

/**
 * _atoi - converts string to integer
 *@c: pointer to a str
 *Return: int
 */
int _atoi(char *c)
{
	int j = 0, i = 0, sgn = 1;

	while (!((c[j] >= '0') && (c[j] <= '9')) && (c[j] != '\0'))
	{
		if (c[j] == '-')
			sgn = sgn * (-1);
		j++;
	}
	while ((c[j] >= '0') && (c[j] <= '9'))
	{
		i = (i * 10) + (sgn * (c[j] - '0'));
		j++;
	}
	return (i);
}

/**
 * env - prints current environment
 * @av: array
 */
void env(char **av __attribute__ ((unused)))
{
	int j;

	for (j = 0 ; envir[j]; j++)
	{
		_puts(envir[j]);
		_puts("\n");
	}
}

/**
 * __setenv - Initialize new environment variable, or modify an existing
 * @av: array
 */
void __setenv(char **av)
{
	int a, b, c;

	if (!av[1] || !av[2])
	{
		perror(_getenv("_"));
		return;
	}
	for (a = 0; envir[a]; a++)
	{
		b = 0;
		if (av[1][b] == envir[a][b])
		{
			while (av[1][b])
			{
				if (av[1][b] != envir[a][b])
					break;
				b++;
			}
			if (av[1][b] == '\0')
			{
				c = 0;
				while (av[2][c])
				{
					envir[a][b + c + 1] = av[2][c];
					c++;
				}
				envir[a][b + c + 1] = '\0';
				return;
			}
		}
	}
	if (!envir[a])
	{
		envir[a] = concat_all(av[1], "=", av[2]);
		envir[a + 1] = '\0';
	}
}

/**
 * __unsetenv - remove environment variable
 * @av: array of words
 */
void __unsetenv(char **av)
{
	int a, b;

	if (!av[1])
	{
		perror(_getenv("_"));
		return;
	}
	for (a = 0 ; envir[a] ; a++)
	{
		b = 0;
		if (av[1][b] == envir[a][b])
		{
			while (av[1][b])
			{
				if (av[1][b] != envir[a][b])
					break;
				b++;
			}
			if (av[1][b] == '\0')
			{
				free(envir[a]);
				envir[a] = envir[a + 1];
				while (envir[a])
				{
					envir[a] = envir[a + 1];
					a++;
				}
				return;
			}
		}
	}
}
