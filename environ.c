#include "shell.h"

/**
* _myenv - This function displays(prints) the current environment
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
* Return: Always 0
*/
int _myenv(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
* _getenv - This function acquires the value of an environ variable
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
* @name: This is the enviroment’s variable name
*
* Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* _mysetenv - generates a new environment variable,
*  or changes an already existing one
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
*  Return: Always 0
*/
int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* _myunsetenv - This function pulls an environment variable
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
* Return: Always 0
*/
int _myunsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
_unsetenv(info, info->argv[i]);

return (0);
}

/**
* populate_env_list - This function fills the env linked list
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
* Return: Always 0
*/
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
