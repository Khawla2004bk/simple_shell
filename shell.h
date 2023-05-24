#ifndef SHELL_H
#define SHELL_H

#define PROMPT_MSG "$"
#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1050

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * struct data_info - struct for data
 * @progname: name of the executable
 * @linput: pointer to the input
 * @namecmd: pointer to the first command typed
 * @countexec: number of excecuted cmds
 * @filedesc: file descriptor
 * @tok: pointer to array
 * @envt: copy of the env
 * @aliasl: array of pointer
 */
typedef struct data_info
{
	char *progname;
	char *linput;
	char *namecmd;
	int countexec;
	int filedesc;
	char **tok;
	char **envt;
	char **aliasl;
} datas;

/**
 * struct builtin_s - struct for the builtins
 * @built: the name of the builtin
 * @funct: the associated function to be called for each builtin
 */
typedef struct builtin_s
{
	char *built;
	int (*funct)(datas *info);
} builtin_s;

int logic_ops(char *cmds[], int x, char oprs[]);
int addbuf(char *buf, char *str);
char *str_tok(char *l, char *del);
void freearr(char **dir);
int setdir(datas *info, char *ndir);
char *get_key(char *N, datas *info);
int set_key(char *k, char *val, datas *info);
int remove_key(char *k, datas *info);

void datainit(datas *info, int ac, char **av, char **envt);
void Prompt(char *p, datas *info);
void ctrl_c(int op UNUSED);

int set_dir(datas *info, char *ndir);
void expandvar(datas *info);
void expandals(datas *info);
void token(datas *info);
int execute(datas *info);
int builtinl(datas *info);
char **pathtoken(datas *info);
int progfind(datas *info);
void recurdata_free(datas *info);
void free_all(datas *info);
int exiit(datas *info);
int _cd(datas *info);
int _help(datas *info);
int _alias(datas *info);
int _env(datas *info);
int set_env(datas *info);
int unset_env(datas *info);
void printenv(datas *info);

char *get_als(datas *info, char *als);
int set_als(char *str, datas *info);
int printals(datas *info, char *als);
int __print(char *str);
int print_error(int error, datas *info);
int str_len(char *str);
char *str_dup(char *str);
int str_cmp(char *str1, char *str2, int num);
char *concat_str(char *str1, char *str2);
void str_rev(char *str);
void int_str(long num, char *str, int b);
int __atoi(char *c);
int char_count(char *str, char *c);
int checkfile(char *full);
int mgetline(datas *info);

#endif
