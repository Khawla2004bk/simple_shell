#include "shell.h"

/**
 * mgetline - Read The Input
 * Return: Input
 */
char *mgetline(void)
{
	static char buf[MAX_BUFFER_SIZE];
	static int indxbuf = 1, buf_size = 1;
	char curchar = buf[indxbuf++], *l = NULL;
	int length = 0;

	while (1)
	{
		if (indxbuf >= buf_size)
		{
			buf_size = read(STDIN_FILENO, buf, sizeof(buf));
			indxbuf = 0;
			if (buf_size <= 0)
			{
				if (length > 0)
					break;
				return (NULL);
			}
		}
		if (curchar == '\n')
			break;
		l = realloc(l, (length + 1) * sizeof(char));
		l[length++] = curchar;
	}
	l = realloc(l, (length + 1) * sizeof(char));
	l[length] = '\0';
	return (l);
}

/**
 * main - Entry point
 * Return: 0
 */
int main(void)
{
	char *inpt = mgetline();

	printf("#cisfun$ ");
	fflush(stdout);
	if (inpt != NULL)
	{
		printf("This is the input: %s\n", inpt);
		free(inpt);
	}
	else
		printf("There is no input\n");
	return (0);
}
