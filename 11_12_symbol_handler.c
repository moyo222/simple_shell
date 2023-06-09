#include "main.h"

/**
* is_chain - This is a function that tests if the
* current char in buffer is a chain delimeter
* @info: This is the parameter struct
* @buf: This is the char buffer
* @p: This is the address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
* check_chain - This is a function that checks if we should
* continue chaining based on last status
* @info: This is the parameter struct
* @buf: This is the char buffer
* @p: This is the address of current position in buf
* @i: This is the starting position in buf
* @len: This is the length of the buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}

*p = j;
}

/**
* replace_alias - This is a function that replaces
* aliases in the tokenized string
* @info: This is the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = shell_strchr(node->str, '=');
if (!p)
return (0);
p = shell_strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}


/**
* replace_string - This is a function that replaces a string
* @old: This is the address of an old string
* @new: This is a new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
