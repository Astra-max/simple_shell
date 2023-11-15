#include "shell.h"

/**
 * astra_env - env variables
 * @info: potential arguments.
 * Return: Always 0
 */
int astra_env(info_t *info)
{
list_content(info->env);
return (0);
}

/**
 * env_values - values of environ variable
 * @info: potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *env_values(info_t *info, const char *name)
{
char *p;
list_t *node = info->env;

while (node)
{
p = string_workon(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * astra_setenv - Initialize a new environment variable,
 *  or modify an existing one
 * @info: potential arguments.
 * Return: Always 0
 */

int astra_setenv(info_t *info)
{
if (info->argc != 3)
{
command_error("Invalid argument number!\n");
return (1);
}
if (create_envv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * astra_unsetenv - Remove an environment variable
 * @info: potential arguments.
 *  Return: Always 0
 */

int astra_unsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
command_error("Invalid number of arguements!\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
remove_envv(info, info->argv[i]);

return (0);
}

/**
 * loop_thru_envv - populates env linked list
 * @info: potential arguments.
 * Return: Always 0
 */

int loop_thru_envv(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
newend_node(&node, environ[i], 0);
info->env = node;
return (0);
}
