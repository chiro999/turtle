#include "shell.h"

/**
 * _execute - Executes a command in the path
 * @command: Full path to the command
 * @shell_vars: Pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int _execute(char *command, shell_t *shell_vars)
{
    pid_t child_process;

    if (access(command, X_OK) == 0)
    {
        child_process = fork();

        if (child_process == -1)
        {
            print_error(shell_vars, "Fork failed\n");
            return 1; /* Return 1 on failure */
        }

        if (child_process == 0)
        {
            /* Attempt to execute the command using execve() */
            if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
            {
                print_error(shell_vars, "Execution failed\n");
                return 1; /* Return 1 on failure */
            }
        }
    }
    else
    {
        /* Handle the case where access to the command is denied */
        print_error(shell_vars, "Access denied\n");
        return 1; /* Return 1 on failure */
    }

    return 0; /* Return 0 on success */
}

/**
 * is_PATH - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success (if '/' is found), 0 on failure (if '/' is not found)
 */
int is_PATH(char *name)
{
    unsigned int i;

    for (i = 0; name[i]; i++)
    {
        if (name[i] == '/')
            return 1;
    }

    return 0;
}

/**
 * str_path - finds the PATH variable
 * @env_arr: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *str_path(char **env_arr)
{
    char *path = "PATH=";
    unsigned int i = 0, j;

    while (env_arr[i] != NULL)
    {
        for (j = 0; j < 5; j++)
        {
            if (path[j] != env_arr[i][j])
                break;
        }
        if (j == 5)
            break;

        i++;
    }

    return (env_arr[i]);
}
