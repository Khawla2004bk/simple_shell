#include "shell.h"

char *mgetline()
{
	static char buf[MAX_BUFFER_SIZE];
	static int indxbuf = 0, buf_size = 0;
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
				else
					return NULL;
			}
		}
		if (curchar == '\n')
			break;
		l = realloc(l, (length + 1) * sizeof(char));
		l[length++] = curchar;
	}
	l = realloc(l, (length + 1) * sizeof(char));
	l[length] = '\0';
	return l;
}

/**
 * main - Entry point
 * Return: 0
 */
int main()
{
	char *inpt = mgetline();

	printf("alex@~$ ");
	fflush(stdout);
	if (inpt != NULL)
	{
		printf("This is the input: %s\n", inpt);
		free(inpt);
	}
	else
		printf("There is no input\n");
	return 0;
}
