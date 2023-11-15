#include "shell.h"

/**
 * mash_strlen - returns the length of a string
 * @data: string to check its len
 *
 * Return: integer length of string
 */
int mash_strlen(char *data)
{
int i = 0;

if (!data)
return (0);

while (*data++)
i++;
return (i);
}

/**
 * mash_strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int mash_strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
 * string_workon - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *string_workon(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
 * mash_strcat - adds two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
 */

char *mash_strcat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
