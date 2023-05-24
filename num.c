#include "shell.h"

/**
 * int_str - Converts number to string
 * @num: number to be converted in string
 * @str: buffer to save the number as str
 * @b: base to convert num
 */
void int_str(long num, char *str, int b)
{
	int i = 0, inegative = 0;
	long c = num;
	char lets[] = {"0123456789abcdef"};

	if (c == 0)
		str[i++] = '0';
	if (str[0] == '-')
		inegative = 1;
	while (c)
	{
		if (c < 0)
			str[i++] = lets[-(c % b)];
		else
			str[i++] = lets[c % b];
		c /= b;
	}
	if (inegative)
		str[i++] = '-';
	str[i] = '\0';
	str_rev(str);
}

/**
 * __atoi - Convert string to integer
 * @c: pointer to str
 * Return: int of str or 0
 */
int __atoi(char *c)
{
	int sgn = 1;
	unsigned int num = 0;

	while (!('0' <= *c && *c <= '9') && *c != '\0')
	{
		if (*c == '-')
			sgn *= -1;
		if (*c == '+')
			sgn *= +1;
		c++;
	}
	while ('0' <= *c && *c <= '9' && *c != '\0')
	{
		num = (num * 10) + (*c - '0');
		c++;
	}
	return (num * sgn);
}

/**
 * char_count - Count coincidences of character in string
 * @str: pointer to str
 * @c: string with chars
 * Return: int of string or 0
 */
int char_count(char *str, char *c)
{
	int x = 0, count = 0;

	for (; str[x]; x++)
	{
		if (str[x] == c[0])
			count++;
	}
	return (count);
}
