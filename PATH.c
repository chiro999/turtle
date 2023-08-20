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

int exec_curr_dir(shell_t *shell_vars)
{
    pid_t child_process;

    if (access(shell_vars->tokens[0], F_OK) == 0)
    {
        if (access(shell_vars->tokens[0], X_OK) == 0)
        {
            child_process = fork();
            if (child_process == -1)
                print_error(shell_vars, NULL);
            if (child_process == 0)
            {
                if (execve(shell_vars->tokens[0], shell_vars->tokens, shell_vars->env_vars) == -1)
                    print_error(shell_vars, NULL);
            }
            else
            {
                wait(&shell_vars->close_status);
                if (WIFEXITED(shell_vars->close_status))
                    shell_vars->close_status = WEXITSTATUS(shell_vars->close_status);
                else if (WIFSIGNALED(shell_vars->close_status) && WTERMSIG(shell_vars->close_status) == SIGINT)
                    shell_vars->close_status = 130;
                return 0;
            }
            shell_vars->close_status = 127;
            return 1;
        }
        else
        {
            print_error(shell_vars, ": Permission denied\n");
            shell_vars->close_status = 126;
        }
        return 0;
    }
    print_error(shell_vars, ": not found\n");
    shell_vars->close_status = 127;
    return 0;
}

void path_check(shell_vars *shell_vars)
{
    char *path, *replica = NULL, *check = NULL;
    unsigned int i = 0, run_cmd = 0;
    char **path_tokens;

    if (check_dir(shell_vars->tokens[0]))
        run_cmd = exec_cwd(shell_vars);
    else
    {
        path = find_path(shell_vars->env_vars);
        if (path != NULL)
        {
            replica = _strdup(path + 5);
            path_tokens = custom_tokenizer(replica, ":");
            for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
            {
                check = _strcat(path_tokens[i], shell_vars->tokens[0]);
                if (access(check, F_OK) == 0)
                {
                    run_cmd = _execute(check, shell_vars);
                    free(check);
                    break;
                }
            }
            free(replica);
            if (path_tokens == NULL)
            {
                shell_vars->close_status = 127;
                _close(shell_vars);
            }
        }
        if (path == NULL || path_tokens[i] == NULL)
        {
            print_error(shell_vars, ": not found\n");
            shell_vars->close_status = 127;
        }
        free(path_tokens);
    }
    if (run_cmd == 1)
        _close(shell_vars);
}
