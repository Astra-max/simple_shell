#include "shell.h"

/**
 * history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *history_file(info_t *info)
{
char *buf, *dir;

dir = env_values(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (mash_strlen(dir) + mash_strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
copy_to(buf, dir);
mash_strcat(buf, "/");
mash_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * record_history - creates a file | adds to an existing file
 * @info: the parameter struct
 *
 * Return: 1 success, else -1
 */

int record_history(info_t *info)
{
ssize_t fd;
char *filename = history_file(info);
list_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
string_command(node->str, fd);
character_to_file('\n', fd);
}
character_to_file(-1, fd);
close(fd);
return (1);
}

/**
 * access_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int access_history(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = history_file(info);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
addto_history(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
addto_history(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
remove_nodeIdx(&(info->history), 0);
update_history(info);
return (info->histcount);
}

/**
 * addto_history - adds entry to a history file linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int addto_history(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;

if (info->history)
node = info->history;
newend_node(&node, buf, linecount);

if (!info->history)
info->history = node;
return (0);
}

/**
 * update_history - updates history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int update_history(info_t *info)
{
list_t *node = info->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
