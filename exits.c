#include "shell.h"

/**
 **copy_string - copies a string
 *@dest: destination string to be copied to
 *@src: source string
 *@n: amount of characters to be copied
 *Return: concatenated string
 */
char *copy_string(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;

while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
 **combine_strings - adds two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */

char *combine_strings(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
 **string_search - locates a char in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: pointer to the memory areas
 */

char *string_search(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
