#include "shell.h"

/**
* checkbuild - checks if command is buildin
* @av: array
* Return: pointer
*/
void(*checkbuild(char **av))(char **av)
{
	int x, y;
	build B[] = {
		{"exit", exiit},
		{"env", env},
		{"setenv", __setenv},
		{"unsetenv", __unsetenv},
		{NULL, NULL}
	};
	for (x = 0 ; B[x].N; x++)
	{
		y = 0;
		if (B[x].N[y] == av[0][y])
		{
			for (y =  0; av[0][y] ; y++)
			{
				if (B[x].N[y] != av[0][y])
					break;
			}
			if (!av[0][y])
				return (B[x].funct);
		}
	}
	return (0);
}
