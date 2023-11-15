#include "shell.h"

/**
 * clean_me - initializes info_t struct
 * @info: struct address
 */

void clean_me(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
 * init_struct - initializes buffer struct
 * @info: struct address
 * @av: argument vector
 */

void init_struct(info_t *info, char **av)
{
int i = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = mash_strtow(info->arg, " \t");
if (!info->argv)
{

info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = astra_strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;

aliasing(info);
sys_vars(info);
}
}

/**
 * free_ram - clears buffer field for nxt command
 * @info: struct address
 * @all: true if freeing all fields
 */

void free_ram(info_t *info, int all)
{
free_buffer(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
clear_all(&(info->env));
if (info->history)
clear_all(&(info->history));
if (info->alias)
clear_all(&(info->alias));
free_buffer(info->environ);
info->environ = NULL;
free_me((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(-1);
}
}
