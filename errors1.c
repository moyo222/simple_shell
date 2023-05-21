#include "main.h"

/**
* print_error - This function prints an error message
* @info: This is the parameter & return info structure
* @estr: This is the string containing the specified error type
* Return: 0 if no numbers in string, converted number otherwise
*  -1 on error
*/
void print_error(info_t *info, char *estr)
{
er_puts(info->fname);
er_puts(": ");
print_deci(info->line_count, STDERR_FILENO);
er_puts(": ");
er_puts(info->argv[0]);
er_puts(": ");
er_puts(estr);
}

/**
* print_deci - This is the function that
* prints a decimal (integer) number (base 10)
* @input: This refers to the input
* @fd: Thus is the file descriptor to write to
*
* Return: number of characters printed
*/
int print_deci(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = er_putchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number - This is a converter function that is an itoa copy
* @num: This is the number
* @base: This is the base
* @flags: Thus is the argument flags
*
* Return: string
*/
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';

}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do	{
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* remove_comments - This is a function that replaces
* the first instance of '#' with '\0'
* @buf: This is the address of the string to modify
*
* Return: Always 0;
*/
void remove_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
