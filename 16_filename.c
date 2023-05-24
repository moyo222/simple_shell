#include "main.h"

/**
* put_fd - This is a function that writes the
* character c to the given file descriptor
* @c: This is the character to be printed
* @fd: This is the file descriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int put_fd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* puts_fd - This function prints an input string
* @str: This refers to the string to be printed
* @fd: This is the file descriptor to be written to
*
* Return: the number of chars put
*/
int puts_fd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += put_fd(*str++, fd);
}
return (i);
}
