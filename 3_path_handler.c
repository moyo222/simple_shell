#include "main.h"


/**
* find_path - This is a function finds the cmd in the PATH string
* @info: This is the info struct
* @pathstr: This refers to the PATH string
* @cmd: This is the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((shell_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (exec_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicate_chars(pathstr, curr_pos, i);
if (!*path)
shell_strcat(path, cmd);
else
{
shell_strcat(path, "/");
shell_strcat(path, cmd);
}
if (exec_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;

path = find_path(info, get_env(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive(info) || get_env(info, "PATH=")
|| info->argv[0][0] == '/') && exec_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
	}
}

/**
* fork_cmd - This is a function that forks an exec thread to run cmd
* @info: This is the parameter & return info struct
*
* Return: void
*/
void fork_cmd(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
