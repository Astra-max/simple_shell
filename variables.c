#include "shell.h"

/**
 * chain_delim - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_delim(info_t *info, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = 1;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = 2;
}
else if (buf[j] == ';') /* EoC End of comm */
{
buf[j] = 0; /* semicolon substituted  with null */
info->cmd_buf_type = 3;
}
else
return (0);
*p = j;
return (1);
}

/**
 * chain_it - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void chain_it(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (info->cmd_buf_type == 2)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == 1)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}

*p = j;
}

/**
 * aliasing - finding & working with alias from tokenzed comm str
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int aliasing(info_t *info)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = start_point(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = string_search(node->str, '=');
if (!p)
return (0);
p = astra_strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}

/**
 * sys_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int sys_vars(info_t *info)
{
int i = 0;
list_t *node;

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;

if (!mash_strcmp(info->argv[i], "$?"))
{
substt_string(&(info->argv[i]), astra_strdup(clone_itoa(info->status, 10, 0)));
continue;
}
if (!mash_strcmp(info->argv[i], "$$"))
{
substt_string(&(info->argv[i]), astra_strdup(clone_itoa(getpid(), 10, 0)));
continue;
}
node = start_point(info->env, &info->argv[i][1], '=');
if (node)
{
substt_string(&(info->argv[i]),
astra_strdup(string_search(node->str, '=') + 1));
continue;
}
substt_string(&info->argv[i], astra_strdup(""));
}
return (0);
}

/**
 * substt_string - substitutes strings old with new
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if truely replaced
 */

int substt_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
