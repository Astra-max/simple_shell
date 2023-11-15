#include "shell.h"

/**
 *command_error - prints out  input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void command_error(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
command_error1(str[i]);
i++;
}
}

/**
 * command_error1 - prints character  to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned
 */

int command_error1(char c)
{
static int i;
static char buf[1024];

if (c == -1 || i >= 1024)
{
write(2, buf, i);
i = 0;
}
if (c != -1)
buf[i++] = c;
return (1);
}

/**
 * character_to_file - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 */

int character_to_file(char c, int fd)
{
static int i;
static char buf[1024];

if (c == -1 || i >= 1024)
{
write(fd, buf, i);
i = 0;
}
if (c != -1)
buf[i++] = c;
return (1);
}

/**
 *string_command - prints out input string
 * @str: string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */

int string_command(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += character_to_file(*str++, fd);
}
return (i);
}
