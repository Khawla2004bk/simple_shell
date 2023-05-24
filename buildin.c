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
		b = __atoi(av[1]);
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
 * __atoi - converts string to integer
 *@c: pointer to a str
 *Return: int
 */
int __atoi(char *c)
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
 * _env - prints current environment
 * @av: array
 */
void _env(char **av __attribute__ ((unused)))
{
	int j;

	for (j = 0 ; environ[j]; j++)
	{
		__puts(environ[j]);
		__puts("\n");
	}
}

/**
 * _setenv - Initialize environment variable, or modify
 * @av: array
 */
void _setenv(char **av)
{
	int a, b, c;

	if (!av[1] || !av[2])
	{
		perror(__getenv("_"));
		return;
	}
	for (a = 0; environ[a]; a++)
	{
		b = 0;
		if (av[1][b] == environ[a][b])
		{
			while (av[1][b])
			{
				if (av[1][b] != environ[a][b])
					break;
				b++;
			}
			if (av[1][b] == '\0')
			{
				c = 0;
				while (av[2][c])
				{
					environ[a][b + c + 1] = av[2][c];
					c++;
				}
				environ[a][b + c + 1] = '\0';
				return;
			}
		}
	}
	if (!environ[a])
	{
		environ[a] = concat(av[1], "=", av[2]);
		environ[a + 1] = '\0';
	}
}

/**
 * _unsetenv - remove environment variable
 * @av: array of words
 */
void _unsetenv(char **av)
{
	int a, b;

	if (!av[1])
	{
		perror(__getenv("_"));
		return;
	}
	for (a = 0 ; environ[a] ; a++)
	{
		b = 0;
		if (av[1][b] == environ[a][b])
		{
			while (av[1][b])
			{
				if (av[1][b] != environ[a][b])
					break;
				b++;
			}
			if (av[1][b] == '\0')
			{
				free(environ[a]);
				environ[a] = environ[a + 1];
				while (environ[a])
				{
					environ[a] = environ[a + 1];
					a++;
				}
				return;
			}
		}
	}
}
