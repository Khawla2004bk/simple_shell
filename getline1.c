#include "shell.h"

/**
 * mgetline - Read The Input
 * Return: Input
 */
char *mgetline(void)
{
	int j = 0;
	ssize_t r;
	char i = 0, *buff = malloc(sizeof(char) * BUFFER_SIZE);

	if (buff == NULL)
		return (NULL);
	while (i != EOF && i != '\n')
	{
		r = read(STDIN_FILENO, &i, 1);
		if (r == 0 || r == -1)
		{
			free(buff);
			if (r == 0)
				exit(EXIT_SUCCESS);
			if (r == -1)
				perror("Error: ");
		}
		buff[j] = i;
		if (buff[0] == '\n')
		{
			free(buff);
			return ("\0");
		}
		if (j + 1 >= BUFFER_SIZE)
		{
			buff = __realloc(buff, j + 1);
			if (buff == NULL)
			{
				free(buff);
				return (NULL);
			}
		}
		j++;
	}
	buff[j - 1] = '\0';
	_handler(buff);
	return (buff);
}

/**
 * _handler - handle hash character
 * @buf: input
 */
void _handler(char *buf)
{
	int j = 0;

	while (buf[j] != '\0')
	{
		if (buf[j] == '#')
			buf[j] = '\0';
		j++;
	}
}
