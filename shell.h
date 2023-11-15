#ifndef SHELL_H
#define SHELL_H

/* Libraries needed for code exe */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Macros i need */

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX  4096

/* For external environ */

extern char **environ;

/* Be sure to have read the reame correctly is you */
/* encounter some issues fill free to contact the */
/* developer via email or phone number */

/**
 * struct liststr - cool singly linked list data strs
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/* Preserve for sysstem files */

/**
 *struct passinfo - args to pass into a func
 *@arg: string generated from getline containing arguements
 *@argv: array of strings generated from arg
 *@path: string path for the current command
 *@argc: arg count
 *@line_count: error count
 *@err_num: error code for exit
 *@linecount_flag: count this line of input
 *@fname: programs name
 *@env: linkedlist local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@env_changed: environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* loop.c */
int mash_hsh(info_t *, char **);
int sys_builtin(info_t *);
void locate_command(info_t *);
void create_commandproc(info_t *);

/* parser.c */
int validate_command(info_t *, char *);
char *multiply_strchar(char *, int, int);
char *locate_command_str(info_t *, char *, char *);

/* loopshell.c */
int loop_hsh(char **);

/* astra_errors.c */
void command_error(char *);
int command_error1(char);
int character_to_file(char c, int fd);
int string_command(char *str, int fd);

/* astra_string.c */
int mash_strlen(char *);
int mash_strcmp(char *, char *);
char *string_workon(const char *, const char *);
char *mash_strcat(char *, char *);

/* astra_string1.c */
char *copy_to(char *, char *);
char *astra_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *copy_string(char *, char *, int);
char *combine_strings(char *, char *, int);
char *string_search(char *, char);

/* token.c */
char **mash_strtow(char *, char *);
char **mash_strtow2(char *, char);

/* realloc.c */
char *astra_memeset(char *, char, unsigned int);
void free_buffer(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* alloc_mem.c */
int free_me(void **);

/* astra_atoi.c */
int command_from_terminal(info_t *);
int check_delimiter(char, char *);
int check_alpha(int);
int is_atoi(char *);

/* astra_errors1.c */
int string_int(char *);
void p_error(info_t *, char *);
int decimals(int, int);
char *clone_itoa(long int, int, int);
void like_preprocessor(char *);

/* astra_builtin.c */
int astra_exit(info_t *);
int astra_cd(info_t *);
int astra_help(info_t *);

/* astra_builtin1.c */
int astra_history(info_t *);
int astra_alias(info_t *);

/*astra_getline.c */
ssize_t command_without_newlineCh(info_t *);
int astra_getline(info_t *, char **, size_t *);
void astra_terminal(int);

/* info.c */
void clean_me(info_t *);
void init_struct(info_t *, char **);
void free_ram(info_t *, int);

/* astra_environ.c */
char *env_values(info_t *, const char *);
int astra_env(info_t *);
int astra_setenv(info_t *);
int astra_unsetenv(info_t *);
int loop_thru_envv(info_t *);

/* env.c */
char **current_location(info_t *);
int remove_envv(info_t *, char *);
int create_envv(info_t *, char *, char *);

/* command_history.c */
char *history_file(info_t *info);
int record_history(info_t *info);
int access_history(info_t *info);
int addto_history(info_t *info, char *buf, int linecount);
int update_history(info_t *info);

/* astra_lists.c */
list_t *beginning_node(list_t **, const char *, int);
list_t *newend_node(list_t **, const char *, int);
size_t list_content(const list_t *);
int remove_nodeIdx(list_t **, unsigned int);
void clear_all(list_t **);

/* astra_lists1.c */
size_t lists_length(const list_t *);
char **strings_from_ll(list_t *);
size_t astra_return_elements(const list_t *);
list_t *start_point(list_t *, char *, char);
ssize_t locate_node(list_t *, list_t *);

/* variables.c and others */
int chain_delim(info_t *, char *, size_t *);
void chain_it(info_t *, char *, size_t *, size_t, size_t);
int aliasing(info_t *);
int sys_vars(info_t *);
int substt_string(char **, char *);

#endif /* SHELL_H */
