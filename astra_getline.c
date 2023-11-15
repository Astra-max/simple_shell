#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* write something to buffer if empty */
{
free(*buf);
*buf = NULL;
signal(SIGINT, astra_terminal);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = astra_getline(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* clears trailing \n character */
r--;
}
info->linecount_flag = 1;
like_preprocessor(*buf);
addto_history(info, *buf, info->histcount++);
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}

/**
 * command_without_newlineCh - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t command_without_newlineCh(info_t *info)
{
static char *buf; /* ';' -> command chaining */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;

_putchar(-1);
r = input_buf(info, &buf, &len);
if (r == -1) /* checks for end of file */
return (-1);
if (len)
{
j = i;
p = buf + i;

chain_it(info, buf, &j, i, len);
while (j < len)
{
if (chain_delim(info, buf, &j))
break;
j++;
}

i = j + 1;
if (i >= len) /* check the entire command feed from terminal */
{
i = len = 0;
info->cmd_buf_type = 0;
}

*buf_p = p;
return (mash_strlen(p)); /* Return lenght of comm feed for execution */
}

*buf_p = buf;
return (r);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(info->readfd, buf, 1024);
if (r >= 0)
*i = r;
return (r);
}

/**
 * astra_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int astra_getline(info_t *info, char **ptr, size_t *length)
{
static char buf[1024];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = string_search(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = reallocate_memory(p, s, s ? s + k : k + 1);
if (!new_p)
return (p ? free(p), -1 : -1);

if (s)
combine_strings(new_p, buf + i, k - i);
else
copy_string(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * astra_terminal - terminal and blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void astra_terminal(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("([mash])~$ ");
_putchar(-1);
}
