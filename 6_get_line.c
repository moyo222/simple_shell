#include "main.h"

/*
* input_buf - These are chained command buffers
* @info: Thus is the parameter structure
* @buf: This is the address of the buffer
* @len: This is the address of the len var
*
* Return: bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, signintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = get_line(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
/* if (shell_strchr(*buf, ';')) is this a command chain? */
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}

/**
* get_input - This is a function that gets a line excluding the newline
* @info: This is the parameter structure
*
* Return: bytes read
*/
ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *PTR;

_putchar(BUF_FLUSH);
r = input_buf(info, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
PTR = buf + i; /* get pointer for return */

check_chain(info, buf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (is_chain(info, buf, &j))
break;
j++;
}

i = j + 1; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
info->cmd_buf_type = CMD_NORM;
}

*buf_p = PTR; /* pass back pointer to current command position */
return (shell_strlen(PTR)); /* return length of current command */
}

*buf_p = buf; /* else not a chain, pass back buffer from get_line() */
return (r); /* return length of buffer from get_line() */
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
r = read(info->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
* get_line - This is a function that gets the next line of input from STDIN
* @info: This is a parameter structure
* @ptr: This is the address of a pointer to buffer, preallocated or NULL
* @length: This is the size of the preallocated ptr buffer if not NULL
*
* Return: s
*/
int get_line(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
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

c = shell_strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = memory_realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
shell_strncat(new_p, buf + i, k - i);
else
shell_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* signintHandler - This is a function that blocks ctrl-C
* @sig_num: This is the signal number
*
* Return: void
*/
void signintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
