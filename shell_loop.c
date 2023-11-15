#include "shell.h"

/**
 * mash_hsh - loops our shell program
 * @info: parameter and return info struct
 * @av: the argument vector from main function
 *
 * Return: 0 on success
 */
int mash_hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clean_me(info);
if (command_from_terminal(info))
_puts("([mash])~$ ");
command_error1(-1);
r = command_without_newlineCh(info);
if (r != -1)
{
init_struct(info, av);
builtin_ret = sys_builtin(info);
if (builtin_ret == -1)
locate_command(info);
}
else if (command_from_terminal(info))
_putchar('\n');
free_ram(info, 0);
}
record_history(info);
free_ram(info, 1);
if (!command_from_terminal(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
 * sys_builtin - system builtin command
 * @info: parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int sys_builtin(info_t *info)
{
int i, built_in_ret = -1;

builtin_table builtintbl[] = {
{"exit", astra_exit},
{"env", astra_env},
{"help", astra_help},
{"history", astra_history},
{"setenv", astra_setenv},
{"unsetenv", astra_unsetenv},
{"cd", astra_cd},
{"alias", astra_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (mash_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

/**
 * locate_command - finds a command in PATH
 * @info: parameter and return info struct
 *
 * Return: nothing
 */
void locate_command(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!check_delimiter(info->arg[i], " \t\n"))
k++;
if (!k)
return;

path = locate_command_str(info, env_values(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
create_commandproc(info);
}
else
{
if ((command_from_terminal(info) || env_values(info, "PATH=") ||
info->argv[0][0] == '/') && validate_command(info, info->argv[0]))
create_commandproc(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
p_error(info, "not found\n");
}
}
}

/**
 * create_commandproc - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: nothing
 */
void create_commandproc(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* exit if error */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, current_location(info)) == -1)
{
free_ram(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* exit if error */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
p_error(info, "Permission denied\n");
}
}
}
