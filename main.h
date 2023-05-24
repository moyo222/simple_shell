#ifndef MAIN_H
#define MAIN_H

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

/* prototype for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* prototype for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* prototype for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* @arg: This is a string produced from getline containing arguements
* @argv: This is an array of strings generated from arg
* @path: This is a string path for the present command
* @argc: This is the argument count
* @line_count: This is the error count
* @err_num: This is the error code for exit()s
* @linecount_flag: if this function is on count this line of input
* @fname: This isthe program filename
* @env: This is the local copy of the environ’s linked list
* @environ: This is the custom modified copy of environ from LL env
* @history: This is known as the history node
* @alias: This is referred to as the alias node
* @env_changed: This comes on if the environ was changed
* @status: This is the return status of the last executed command
* @cmd_buf: This function comes on if chaining.
* @cmd_buf_type: This is the CMD_type ||, &&, ;
* @readfd: This is the fd from which to read line input from
* @histcount: This is the number of lines in the history
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

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;


/**
* struct liststr - This is referred to as a singly linked list
* @num: This is the number field
* @str: This is known as a string
* @next: This points to the next node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
* struct builtin - This function contains a builtin
* string and related function
* @type: This is the builtin command flag
* @func: This refers to the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* Prototypes for shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* Prototypes for parser.c */
int exec_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Prototypes for errors.c */
void er_puts(char *);
int er_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* Prototypes for string.c */
int shell_strlen(char *);
int shell_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *shell_strcat(char *, char *);

/* Prototypes for string1.c */
char *shell_strcpy(char *, char *);
char *shell_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Prototypes for exits.c */
char *shell_strncpy(char *, char *, int);
char *shell_strncat(char *, char *, int);
char *shell_strchr(char *, char);

/* Prototypes for tokenizer.c */
char **str_to_word(char *, char *);
char **str_to_word_2(char *, char);

/* Prototypes for realloc.c */
char *memory_set(char *, char, unsigned int);
void ffree(char **);
void *memory_realloc(void *, unsigned int, unsigned int);

/* Prototypes for memory.c */
int bfree(void **);

/* Prototypes for atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Prototypes for errors1.c */
int error_atoi(char *);
void print_error(info_t *, char *);
int print_deci(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Prototypes for builtin.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* Prototypes for builtin1.c */
int shell_history(info_t *);
int shell_alias(info_t *);

/*Prototypes for getline.c */
ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void signintHandler(int);

/* Prototypes for getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Prototypes for environ.c */
char *get_env(info_t *, const char *);
int shell_env(info_t *);
int shell_setenv(info_t *);
int shell_unsetenv(info_t *);
int populate_env_list(info_t *);

/* Prototypes for getenv.c */
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* Prototypes for history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Prototypes for lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Prototypes for lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Prototypes for vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
