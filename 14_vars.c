#include "main.h"

/**
* replace_vars - This is a function that replaces
* variables in the tokenized string
* @info: This is the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
int i = 0;
list_t *node;

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;

if (!shell_strcmp(info->argv[i], "$?"))
{
replace_string(&(info->argv[i]),
shell_strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!shell_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]),
shell_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]),
shell_strdup(shell_strchr(node->str, '=') + 1));
continue;
}
replace_string(&info->argv[i], shell_strdup(""));

}
return (0);
}
