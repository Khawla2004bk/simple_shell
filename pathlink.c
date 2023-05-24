#include "shell.h"

/**
 * __getenv - searches environment list to find environment variable name
 * @N: name of global variable
 * Return: string
 */
char *__getenv(const char *N)
{
	int a, b;
	char *val;

	if (!N)
		return (NULL);

	for (a = 0; environ[a]; a++)
	{
		b = 0;
		if (N[b] == environ[a][b])
		{
			while (N[b])
			{
				if (N[b] != environ[a][b])
					break;

				b++;
			}
			if (N[b] == '\0')
			{
				val = (environ[a] + b + 1);
				return (val);
			}
		}
	}
	return (0);
}

/**
 * add_node - adds a new node at the end of a list
 * @h: our linked list's pointer to its pointer
 * @s: pointer to str in prev first node
 * Return: address of the new node
 */
pathl *add_node(pathl **h, char *s)
{
	pathl *tp;
	pathl *n;

	n = malloc(sizeof(pathl));
	if (!n || !s)
		return (NULL);

	n->d = s;
	n->ptr = '\0';
	if (!*h)
		*h = n;
	else
	{
		tp = *h;
		while (tp->ptr)
			tp = tp->ptr;

		tp->ptr = n;
	}
	return (*h);
}

/**
 * pathlink - paths are converted into a linked list
 * @p: string
 * Return: pointer to created list
 */
pathl *pathlink(char *p)
{
	pathl *h = '\0';
	char *tok, *cp = __strdup(p);

	tok = strtok(cp, ":");
	while (tok)
	{
		h = add_node(&h, tok);
		tok = strtok(NULL, ":");
	}
	return (h);
}

/**
 * __which - discover a file's pathname
 * @file: name of file
 * @h: head of path directories
 * Return: pathname of filename, NULL if no match
 */
char *__which(char *file, pathl *h)
{
	struct stat st;
	char *str;
	pathl *tp = h;

	while (tp)
	{
		str = concat(tp->d, "/", file);
		if (stat(str, &st) == 0)
			return (str);
		free(str);
		tp = tp->ptr;
	}
	return (NULL);
}

/**
 * freel - frees a list
 *@h: pointer to linked list
 */
void freel(pathl *h)
{
	pathl *strg;

	while (h)
	{
		strg = h->ptr;
		free(h->d);
		free(h);
		h = strg;
	}
}
