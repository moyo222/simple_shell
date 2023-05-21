#include "main.h"

/**
* exec_cmd - This is a function that determines
* if a file is an executable command
* @info: This is the info struct
* @path: This refers to the path to the file
*
* Return: 1 if true, 0 otherwise
*/
int exec_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* duplicate_chars - This is a function that clones(duplicates) characters
* @pathstr: This is the PATH string
* @start: This refers to the starting index
* @stop: Thus refers to the stopping index
*
* Return: pointer to new buffer
*/
char *duplicate_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}
