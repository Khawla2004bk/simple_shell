#include "shell.h"

/**
 * expandvar - Expand variables
 * @info: ...
 */
void expandvar(datas *info)
{
	int x, y;
	char l[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (info->linpu == NULL)
		return;
	addbuf(l, info->linput);
	for (x = 0; l[x]; x++)
		if (l[x] == '#')
			l[x--] = '\0';
		else if (l[x] == '$' && l[x + 1] == '?')
		{
			l[x] = '\0';
			int_str(errno, exp, 10);
			addbuf(l, exp);
			addbuf(l, info->linput + x + 2);
		}
		else if (l[x] == '$' && l[x + 1] == '$')
		{
			l[x] = '\0';
			int_str(getpid(), exp, 10);
			addbuf(l, exp);
			addbuf(l, info->linput + x + 2);
		}
		else if (l[x] == '$' && (l[x + 1] == ' ' || l[x + 1] == '\0'))
			continue;
		else if (l[x] == '$')
		{
			for (y = 1; l[x + y] && l[x + y] != ' '; y++)
				exp[y - 1] = l[x + y];
			tmp = get_key(exp, info);
			l[x] = '\0', exp[0] = '\0';
			addbuf(exp, l + x + y);
			tmp ? addbuf(l, tmp) : 1;
			addbuf(l, exp);
		}
	if (!str_cmp(info->linput, l, 0))
	{
		free(info->linput);
		info->linput = str_dup(l);
	}
}

/**
 * expandals - Expans alias
 * @info: ...
 */
void expandals(datas *info)
{
	int x, y, was_exp = 0;
	char l[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (info->linput == NULL)
		return;
	addbuf(l, info->linput);
	for (x = 0; l[x]; x++)
	{
		for (y = 0; l[x + y] && l[x + y] != ' '; y++)
			exp[y] = l[x + y];
		exp[y] = '\0';
		tmp = _alias(info, exp);
		if (tmp)
		{
			exp[0] = '\0';
			addbuf(exp, l + x + y);
			l[x] = '\0';
			addbuf(l, tmp);
			l[str_len(l)] = '\0';
			addbuf(l, exp);
			was_exp = 1;
		}
		break;
	}
	if (was_exp)
	{
		free(info->linput);
		info->linput = str_dup(l);
	}
}

/**
 * addbuf - Append string at the end of buffer
 * @buf: buffer to fill
 * @str: string to copy in buffer
 */
int addbuf(char *buf, char *str)
{
	int len, x;

	len = str_len(buf);
	for (x = 0; str[x]; x++)
		buf[len + x] = str[x];
	buf[len + x] = '\0';
	return (len + x);
}
