#include "shell.h"

/**
 * free_me - frees a pointer to allocate mem
 * @pointer: addrrs of pointer to free
 *
 * Return: 1 true, 0 false
 */
int free_me(void **pointer)
{
if (pointer && *pointer)
{
free(*pointer);
*pointer = NULL;
return (1);
}
return (0);
}
