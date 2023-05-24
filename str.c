#include "shell.h"

/**
 * str_len - returns length of a string
 * @str: pointer to string
 * Return: length of str
 */
int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (str[len++] != '\0')
		;
	return (--len);
}

/**
 * str_dup - duplicates string
 * @str: String to copy
 * Return: pointer to array
 */
char *str_dup(char *str)
{
	char *rslt;
	int len, x;

	if (str == NULL)
		return (NULL);
	len = str_len(str) + 1;
	rslt = malloc(sizeof(char) * len);
	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (x = 0; x < len ; x++)
		rslt[x] = str[x];
	return (rslt);
}

/**
 * str_cmp - compare two strings
 * @str1: String one
 * @str2: String two
 * @num: number of characters
 * Return: 1 if strings are equals, 0 if strings are different
 */
int str_cmp(char *str1, char *str2, int num)
{
	int iter;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (num == 0)
	{
		if (str_len(str1) != str_len(str2))
			return (0);
		for (iter = 0; str1[iter]; iter++)
			if (str1[iter] != str2[iter])
				return (0);
		return (1);
	}
	else
	{
		for (iter = 0; iter < num ; iter++)
		{
			if (str1[iter] != str2[iter])
			return (0);
		}
		return (1);
	}
}

/**
 * concat_str - Concatenates two strings
 * @str1: String
 * @str2: String
 * Return: pointer to array
 */
char *concat_str(char *str1, char *str2)
{
	char *rslt;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_len(str1);
	if (str2 == NULL)
		str2 = "";
	len2 = str_len(str2);
	rslt = malloc(sizeof(char) * (len1 + len2 + 1));
	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; str1[len1] != '\0'; len1++)
		rslt[len1] = str1[len1];
	free(str1);
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		rslt[len1] = str2[len2];
		len1++;
	}
	rslt[len1] = '\0';
	return (rslt);
}

/**
 * str_rev - reverses string
 * @str: pointer to string
 */
void str_rev(char *str)
{
	int x = 0, len = str_len(str) - 1;
	char hld;

	while (x < len)
	{
		hld = str[x];
		str[x++] = str[len];
		str[len--] = hld;
	}
}
