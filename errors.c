#include "main.h"

/**
* er_puts - This is a function that prints an input string
* @str: This indicates the string to be printed
*
* Return: Nothing
*/
void er_puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
er_putchar(str[i]);
i++;
}
}

/**
* er_putchar - This is a function that writes the character c to stderr
* @c: This is the character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int er_putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}



/**
* error_atoi - This is a function that converts a string to an integer
* @s: This is the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*       -1 on error
*/
int error_atoi(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}
