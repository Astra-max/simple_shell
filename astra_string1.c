#include "shell.h"

/**
 * copy_to - copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer
 */
char *copy_to(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * astra_strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer
 */

char *astra_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 *_puts - my puts
 *@str: what to print to stdout
 *
 * Return: Nothing
 */

void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * _putchar - my putchar
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
static int i;
static char buf[1024];

if (c == -1 || i >= 1024)
{
write(1, buf, i);
i = 0;
}
if (c != -1)
buf[i++] = c;
return (1);
}
