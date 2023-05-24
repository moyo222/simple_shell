#include "main.h"

/**
* hsh - This is the main shell loop
* @info: This is the parameter & return info struct
* @av: This is the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("> ");
er_putchar(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
* find_builtin - This is a function that locates a builtin command
* @info: This is the parameter & return info struct
*
* Return: -1 if builtin sorry! command not found ,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int find_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", shell_exit},
{"env", shell_env},
{"help", shell_help},
{"history", shell_history},
{"setenv", shell_setenv},
{"unsetenv", shell_unsetenv},
{"cd", shell_cd},
{"alias", shell_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (shell_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

