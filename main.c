#include "shell.h"

/**
 * main - shell controller
 * @ac: number of arguments
 * @av: Argument vector
 *
 * Return: 0 (success)
 */

int main(int ac, char **av)
{
int fd = 2;
info_t info[] = { INFO_INIT };

/* my assembly code goes here */

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
command_error(av[0]);
command_error(": 0: Can't open ");
command_error(av[1]);
command_error1('\n');
command_error1(-1);
exit(127);
}
return (EXIT_FAILURE);
		}
info->readfd = fd;
}
loop_thru_envv(info);
access_history(info);
mash_hsh(info, av);
return (EXIT_SUCCESS);
}
