#include "shell.h"

/**
 * __strdup - returns pointer to new string which is a duplicate of s
 * @s: string
 * Return: string
 */
char *__strdup(char *s)
{
	int a, b;
	char *n;

	if (!s)
		return (NULL);
	for (b = 0; s[b] != '\0';)
		b++;

	n = malloc(sizeof(char) * b + 1);
	if (!n)
		return (NULL);

	for (a = 0; a < b; a++)
		n[a] = s[a];

	n[b] = s[b];
	return (n);
}

/**
 * concat - Concats 3 strings in freshly allocated memory
 * @N: string 1
 * @spr: string 2
 * @val: string 3
 * Return: new string
 */
char *concat(char *N, char *spr, char *val)
{
	char *rslt;
	int x, y, z, m, n;

	x = __strlen(N);
	y = __strlen(spr);
	z = __strlen(val);
	rslt = malloc(x + y + z + 1);

	if (!rslt)
		return (NULL);
	for (m = 0; N[m]; m++)
		rslt[m] = N[m];

	n = m;
	for (m = 0; spr[m]; m++)
		rslt[n + m] = spr[m];

	n = n + m;
	for (m = 0; val[m]; m++)
		rslt[n + m] = val[m];

	n = n + m;
	rslt[n] = '\0';
	return (rslt);
}

/**
 * __strlen - calculates the length of the string
 * @c: string
 * Return: length of str
 */
int __strlen(char *c)
{
	int a = 0;

	while (*(c + a) != '\0')
		a++;
	return (a);
}

/**
 * __putchar - writes the string s to stream
 * @c: character to be printed
 * Return: On success 1, On error -1, errno is set appropriately
 */
int __putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * __puts - writes the string
 * @s: string
 */
void __puts(char *s)
{
	int a = 0;

	while (s[a])
	{
		__putchar(s[a]);
		a++;
	}
}
