#include "shell.h"

/**
 **astra_memeset -  Fill up memory
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: pointer to the memory areas
 */

char *astra_memeset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
 * free_buffer - clears up string space
 * @pp: string of strings
 */

void free_buffer(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: size of previous block
 * @new_size: size of new block
 *
 * Return: pointer to old memeory block
 */

void *reallocate_memory(void *ptr, unsigned int old_size,
unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}
