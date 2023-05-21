#include "main.h"

/**
**shell_strncpy - This function duplicates a string
*@dest: This is the string to be copied to at the destination.
*@src: This is the source string
*@n: This is the amount of characters to be duplicated
*Return: the concatenated string
*/
char *shell_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
**shell_strncat - This function joins two strings together
*@dest: This refers to the first string
*@src: This refers to the second string
*@n: This refers to the maximum amount of bytes to be used
*Return: the concatenated string
*/
char *shell_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
**shell_strchr - This is a function that finds a character within a string
*@s: This is the string that has to be parsed
*@c: This is the character to locate
*Return: (s) a pointer to the memory area s
*/
char *shell_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
