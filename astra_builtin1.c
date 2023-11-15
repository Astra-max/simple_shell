#include "shell.h"

/**
 * astra_history - returns previous commands from the terminal
 * @comm: command args
 * Return: 0 success
 */
int astra_history(info_t *comm)
{
astra_return_elements(comm->history);

return (0);
}

/**
 * unset_alias - alias to string
 * @comm: parameter struct
 * @todo: the string alias
 *
 * Return: Always 0 on success
 */
int unset_alias(info_t *comm, char *todo)
{
char *m, z;
int i;

m = string_search(todo, '=');
if (!m)
return (1);
z = *m;
*m = 0;
i = remove_nodeIdx(&(comm->alias),
locate_node(comm->alias, start_point(comm->alias, todo, -1)));
*m = z;
return (i);
}

/**
 * set_alias - makes alias from string command
 * @comm: strcut parameter
 * @command: string command
 *
 * Return: Always 0 on success
 */

int set_alias(info_t *comm, char *command)
{
char *m;

m = string_search(command, '=');
if (!m)
return (1);
if (!*++m)
return (unset_alias(comm, command));

unset_alias(comm, command);
return (newend_node(&(comm->alias), command, 0) == NULL);
}

/**
 * print_alias - returns alias created
 * @position: alias position
 *
 * Return: Always 0 on success
 */

int print_alias(list_t *position)
{
char *m = NULL, *b = NULL;

if (position)
{
m = string_search(position->str, '=');
for (b = position->str; b <= m; b++)
_putchar(*b);
_putchar('\'');
_puts(m + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * astra_alias - works as system builtin alias
 * @comm: alias
 * Return: Always 0
 */
int astra_alias(info_t *comm)
{
int i = 0;
char *m = NULL;

list_t *node = NULL;

if (comm->argc == 1)
{
node = comm->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; comm->argv[i]; i++)
{
m = string_search(comm->argv[i], '=');
if (m)
set_alias(comm, comm->argv[i]);
else
print_alias(start_point(comm->alias, comm->argv[i], '='));
}

return (0);
}
