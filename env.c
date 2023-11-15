#include "shell.h"

/**
 * current_location - current env/user location
 * @info: potential arguments.
 * Return: Always 0
 */
char **current_location(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = strings_from_ll(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * remove_envv - Permenent removal of env variable
 * @info: potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */

int remove_envv(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = string_workon(node->str, var);
if (p && *p == '=')
{
info->env_changed = remove_nodeIdx(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
 * create_envv - creates a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */

int create_envv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(mash_strlen(var) + mash_strlen(value) + 2);
if (!buf)
return (1);
copy_to(buf, var);
mash_strcat(buf, "=");
mash_strcat(buf, value);
node = info->env;
while (node)
{
p = string_workon(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
newend_node(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
