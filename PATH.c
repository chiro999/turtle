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
            print_error(shell_vars, "Fork failed\n");

        if (child_process == 0)
        {
            if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
                print_error(shell_vars, "Execution failed\n");
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
        print_error(shell_vars, "Permission denied\n");
        shell_vars->close_status = 126;
    }

    return 0;
}
