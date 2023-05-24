#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 2050
#define BUFFER_SIZE 1050

extern char **environ;
char *concat(char *N, char *spr, char *val);
char **splitstr(char *s, const char *del);
char *__strdup(char *s);
int __strncmp(const char *s1, const char *s2, size_t l);
int __strcmp(const char *s1, const char *s2);
int __strlen(char *c);
int __putchar(char c);
void *__realloc(void *pntr, unsigned int osize, unsigned int nsize);
void _execute(char **av);
void __puts(char *s);
int cd(char *p);

int __atoi(char *c);
void _env(char **av);
void exiit(char **av);
int __setenv(const char *N, const char *val);
int __unsetenv(const char *N);
void _setenv(char **av);
void _unsetenv(char **av);
void (*_checkbuild(char **av))(char **av);

char *__getenv(const char *N);

void freeav(char **av);

void _handler(char *buf);
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
