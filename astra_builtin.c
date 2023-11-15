#include "shell.h"

/**
 * astra_exit - exits the shell
 * @info: potential arguments.
 *  Return: exit status
 */

int astra_exit(info_t *info)
{
int exitcheck;

if (info->argv[1])
{
exitcheck = string_int(info->argv[1]);

if (exitcheck == -1)
{
info->status = 2;
p_error(info, "Illegal number: ");
command_error(info->argv[1]);
command_error1('\n');
return (1);
}
info->err_num = string_int(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * astra_cd - changes the current directory
 * @info: potential arguments.
 *  Return: Always 0
 */

int astra_cd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = env_values(info, "HOME=");
if (!dir)
chdir_ret = /*Change directory*/
chdir((dir = env_values(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (mash_strcmp(info->argv[1], "-") == 0)
{
if (!env_values(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(env_values(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /*  change to New directory */
chdir((dir = env_values(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
p_error(info, "can't cd to ");
command_error(info->argv[1]), command_error1('\n');
}
else
{
create_envv(info, "OLDPWD", env_values(info, "PWD="));
create_envv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * astra_help - will be made available soon
 * @info: potential arguments.
 *  Return: Always 0
 */

int astra_help(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("Currently not available!\n");
if (0)
_puts(*arg_array);
return (0);
}
