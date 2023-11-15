#include "shell.h"

/**
 * command_from_terminal - command from terminal return 1 if true
 * @comm: address of struct comm
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int command_from_terminal(info_t *comm)
{
return (isatty(STDIN_FILENO) && comm->readfd <= 2);
}

/**
 * check_delimiter - checks if character is a delimeter
 * @test: the char to check
 * @delimiter: the delimeter string
 * Return: 1 - true | 0 if false
 */

int check_delimiter(char test, char *delimiter)
{
while (*delimiter)
if (*delimiter++ == test)
return (1);
return (0);
}

/**
 *check_alpha - checks for alphabetic character
 *@input: input char
 *Return: 1 if alpha or otherwise
 */

int check_alpha(int input)
{
if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
return (1);
else
return (0);
}

/**
 *is_atoi - converts a string to an integer
 *@string: test string
 *Return: if no number on string return 0
 */

int is_atoi(char *string)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  string[i] != '\0' && flag != 2; i++)
{
if (string[i] == '-')
sign *= -1;

if (string[i] >= '0' && string[i] <= '9')
{
flag = 1;
result *= 10;
result += (string[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
