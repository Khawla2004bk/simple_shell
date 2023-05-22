#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stddef.h>
/* strtok */
#include <string.h>
/* fork(), execve */
#include <unistd.h>
/* wait */
#include <sys/wait.h>
/* type pid */
#include <sys/types.h>
/* opn files */
#include <fcntl.h>
/* sgnl managmnt */
#include <signal.h>
/*  errno and perror */
#include <errno.h>

#define MAX_BUFFER_SIZE 2050

extern char **environ;
char *concat(char *N, char *spr, char *val);
char **splitstr(char *s, const char *del);
char *__strdup(char *s);
int __strlen(char *c);
int __putchar(char c);
void *__realloc(void *pntr, unsigned int osize, unsigned int nsize);
void _execute(char **av);
void __puts(char *s);

int __atoi(char *c);
void _env(char **av);
void exiit(char **av);
void __setenv(char **av);
void __unsetenv(char **av);
void (*_checkbuild(char **av))(char **av);

char *__getenv(const char *N);

void freeav(char **av);

/**
 * struct pathl - PATH directories are contained in a linked list
 * @d: directory
 * @ptr: pointer to node
 */
typedef struct pathl
{
	char *d;
	struct pathl *ptr;
} pathl;

pathl *add_node(pathl **h, char *s);
pathl *pathlink(char *p);
void freel(pathl *h);
char *__which(char *file, pathl *h);

/**
 * struct build - identifier of funct with the appropriate built-in command
 * @N: cmd
 * @funct: execute cmd
 */
typedef struct build
{
	char *N;
	void (*funct)(char **);
} build;

#endif
