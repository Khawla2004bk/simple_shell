#include "shell.h"

/**
 * str_tok - separates strings
 * @l: pointer to array
 * @del: characters
 * Return: pointer to created token
 */
char *str_tok(char *l, char *del)
{
	int i;
	static char *s;
	char *copy;

	if (l != NULL)
		s = l;
	for (; *s != '\0'; s++)
	{
		for (i = 0; del[i] != '\0'; i++)
		{
			if (*s == del[i])
			break;
		}
		if (del[i] == '\0')
			break;
	}
	copy = s;
	if (*copy == '\0')
		return (NULL);
	for (; *s != '\0'; s++)
	{
		for (i = 0; del[i] != '\0'; i++)
		{
			if (*s == del[i])
			{
				*s = '\0';
				s++;
				return (copy);
			}
		}
	}
	return (copy);
}
