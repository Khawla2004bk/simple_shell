#include "shell.h"

/**
 * splitstring - splits src string into words separated by the characters in sep
 * @str: string to split
 * @del: delimiter
 * Return: arr of pntrs to words
 */
char **splitstring(char *s, const char *del)
{
	int j, w;
	char **ar;
	char *tok;
	char *cp;

	cp = malloc(_strlen(s) + 1);
	if (cp == NULL)
	{
		perror(_getenv("_"));
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
	ar[0] = _strdup(tok);
	j = 1;
	w = 3;
	while (tok)
	{
		tok = strtok(NULL, del);
		ar = _realloc(ar, (sizeof(char *) * (w - 1)),
				(sizeof(char *) * w));
		ar[j] = _strdup(tok);
		j++;
		w++;
	}
	free(cp);
	return (ar);
}

/**
 * execute - executes command
 * @av: array of arg
 */
void execute(char **argv)
{

	int i, stts;

	if (!av || !av[0])
		return;
	i = fork();
	if (i == -1)
		perror(_getenv("_"));
	if (i == 0)
	{
		execve(av[0], av, envir);
			perror(av[0]);
		exit(EXIT_FAILURE);
	}
	wait(&stts);
}

/**
 * _realloc - reallocates memory
 * @pntr: prev pointer
 * @osize: old size
 * @nsize: new size
 * Return: new ptr
 */
void *_realloc(void *pntr, unsigned int osize, unsigned int nsize)
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
