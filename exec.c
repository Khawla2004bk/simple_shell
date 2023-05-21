#include "shell.h"

/**
 * splitstr - splits string into words separated by the characters in sep
 * @s: string to split
 * @del: delimiter
 * Return: arr of pntrs to words
 */
char **splitstr(char *s, const char *del)
{
	int j, w;
	char **ar;
	char *tok;
	char *cp;

	cp = malloc(__strlen(s) + 1);
	if (cp == NULL)
	{
		perror(__getenv("_"));
		return (NULL);
	}
	j = 0;
	while (s[j])
	{
		cp[j] = s[j];
		j++;
	}
	cp[j] = '\0';
	tok = strtok(cp, del);
	ar = malloc((sizeof(char *) * 2));
	ar[0] = __strdup(tok);
	j = 1;
	w = 3;
	while (tok)
	{
		tok = strtok(NULL, del);
		ar = __realloc(ar, (sizeof(char *) * (w - 1)),
				(sizeof(char *) * w));
		ar[j] = __strdup(tok);
		j++;
		w++;
	}
	free(cp);
	return (ar);
}

/**
 * _execute - executes command
 * @av: array of arg
 */
void _execute(char **av)
{

	int i, stts;

	if (!av || !av[0])
		return;
	i = fork();
	if (i == -1)
		perror(__getenv("_"));
	if (i == 0)
	{
		execve(av[0], av, environ);
			perror(av[0]);
		exit(EXIT_FAILURE);
	}
	wait(&stts);
}

/**
 * __realloc - reallocates memory
 * @pntr: prev pointer
 * @osize: old size
 * @nsize: new size
 * Return: new ptr
 */
void *__realloc(void *pntr, unsigned int osize, unsigned int nsize)
{
	char *n;
	char *o;
	unsigned int j;

	if (pntr == NULL)
		return (malloc(nsize));
	if (nsize == osize)
		return (pntr);
	if (nsize == 0 && pntr != NULL)
	{
		free(pntr);
		return (NULL);
	}
	n = malloc(nsize);
	o = pntr;
	if (n == NULL)
		return (NULL);
	if (nsize > osize)
	{
		for (j = 0 ; j < osize ; j++)
			n[j] = o[j];
		free(pntr);
		for (j = osize ; j < nsize ; j++)
			n[j] = '\0';
	}
	if (nsize < osize)
	{
		for (j = 0 ; j < nsize; j++)
			n[j] = o[j];
		free(pntr);
	}
	return (n);
}

/**
 * freeav - frees the array of pointers
 *@av: array
 */
void freeav(char **av)
{
	int j;

	for (j = 0 ; av[j] ; j++)
		free(av[j]);
	free(av);
}
