#include "main.h"

/**
* shell_strlen - This is a function that returns the length of a string
* @s: This is the string whose length is to be checked
*
* Return: integer length of string
*/
int shell_strlen(char *s)
{
int i = 0;

if (!s)
return (0);

while (*s++)
i++;
return (i);
}

/**
* shell_strcmp - This is a function that performs
* alphabetic comparison of two strings.
* @s1: This is the first strang
* @s2: This is the second strang
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int shell_strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
* starts_with - This is a function that checks if a needle starts with haystack
* @haystack: This is the string to search
* @needle: This is the sub-string to find
*
* Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* shell_strcat - This is a funcion that connects two strings
* @dest: This is the destination buffer
* @src: This is the source buffer
*
* Return: pointer to destination buffer
*/
char *shell_strcat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
