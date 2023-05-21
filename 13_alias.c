#include "main.h"

/**
 * unset_alias - This function sets alias to string
 * @info: This is a parameter structure
 * @str: This is the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
char *p, c;
int ret;

p = shell_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - This function is used to set alias to string
 * @info: This is a parameter structure
 * @str: This is the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
char *p;

p = shell_strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));

unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - This function is used to display(print) an alias string
 * @node: This is the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = shell_strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* shell_alias - This function imitates the alias builtin (man alias)
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
*  Return: Always 0
*/
int shell_alias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = shell_strchr(info->argv[i], '=');
if (p)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}
