#include "main.h"

/**
* memory_set - This function fills the memory with a constant byte
* @s: This is the pointer to the memory area
* @b: This is the byte to fill *s with
* @n: This is the number of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *memory_set(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* ffree - This is a function that frees a string of strings
* @pp: This is refferd to as a string of strings
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* memory_realloc - This is a function that reallocates a block of memory
* @ptr: This is a pointer to the previous malloc'ated block
* @old_size: This is the size of the byte of the previous block
* @new_size: This is the byte size of the new block
*
* Return: pointer to da ol'block nameen.
*/
void *memory_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}

/**
 * bfree - This function frees a pointer and NULLs the address
 * @ptr: This is the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}