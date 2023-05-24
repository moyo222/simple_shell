#include "main.h"

/**
 * shell_exit - This function is to exit the shell program.
 * @info: This is a structure that contains potential arguments.
 * It is used to maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
int check_exit;

if (info->argv[1])
{
check_exit = error_atoi(info->argv[1]);
if (check_exit == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
er_puts(info->argv[1]);
er_putchar('\n');
return (1);
}
info->err_num = error_atoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}


/**
 * shell_help - This variable is used to change
 * the current directory of the process
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
 * Return: Always 0
 */
int shell_help(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}

/**
* shell_history - This function displays the history list
* line by line, command by command
*   preceding with line numbers, starting at 0.
* @info: This is a structure that contains potential arguments.
* It is used to maintain constant function prototype.
*  Return: Always 0
*/
int shell_history(info_t *info)
{
print_list(info->history);
return (0);
}
