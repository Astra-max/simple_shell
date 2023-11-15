#include "shell.h"

/**
 * lists_lenght- length of command (linked list)
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t lists_lenght(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
 * strings_from_ll - Gets strings from linked list
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **strings_from_ll(list_t *head)
{
list_t *node = head;
size_t i = lists_lenght(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(mash_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = copy_to(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
 * astra_return_elements - returns all elemts in the linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t astra_return_elements(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts(clone_itoa(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
 * start_point - point in the linked list to start from
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *start_point(list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = string_workon(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * locate_node - locates node to work with
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t locate_node(list_t *head, list_t *node)
{
size_t i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
