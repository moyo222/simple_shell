#include "main.h"

/**
* shell_cd - This function is used to change
* the current directory of the process
* @info: This is a structure that  contains potential arguments.
* It is used to maintain constant function prototype.
* Return: Always 0
*/
int shell_cd(info_t *info)
{
char *s, *dir, buffer[1024];
int change_dir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = get_env(info, "HOME=");
if (!dir)
change_dir_ret = /* TODO: what should this be? */
chdir((dir = get_env(info, "PWD=")) ? dir : "/");
else
change_dir_ret = chdir(dir);
}
else if (shell_strcmp(info->argv[1], "-") == 0)
{
if (!get_env(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(get_env(info, "OLDPWD=")), _putchar('\n');
change_dir_ret = /* TODO: what should this be? */
chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
}
else
change_dir_ret = chdir(info->argv[1]);
if (change_dir_ret == -1)
{
print_error(info, "can't cd to ");
er_puts(info->argv[1]), er_putchar('\n');
}
else
{
set_env(info, "OLDPWD", get_env(info, "PWD="));
set_env(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
