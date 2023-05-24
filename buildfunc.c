#include "shell.h"

/**
* _checkbuild - checks if command is buildin
* @av: array
* Return: pointer
*/
void(*_checkbuild(char **av))(char **av)
{
	int x, y;
	build B[] = {
		{"exit", exiit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
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
