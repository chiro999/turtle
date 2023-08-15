#include "shell.h"

/**
 * _execute - executes a command in the path
 * @command: full path to the command
 * @input_variables: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int _execute(char *command, input_t *input_variables)
{
    pid_t child_process; /* Declare a variable to store the child process ID */

    /* Check if the command is executable (has execute permission) */
    if (access(command, X_OK) == 0)
    {
        /* Create a new process using fork() and store the child process ID */
        child_process = fork();

        /* Check if fork() failed */
        if (child_process == -1)
            _error(input_variables, NULL); /* Call the error handling function */

        /* If this is the child process */
        if (child_process == 0)
        {
            /* Attempt to execute the command using execve() */
            if (execve(command, input_variables->tokens, input_variables->env) == -1)
                _error(input_variables, NULL); /* Call the error handling function */
        }
        /* If this is the parent process */
        else
        {
            /* Wait for the child process to complete */
            wait(&input_variables->status);

            /* Check if the child process exited normally */
            if (WIFEXITED(input_variables->status))
                input_variables->status = WEXITSTATUS(input_variables->status);
            /* Check if the child process was terminated by a signal (e.g., Ctrl+C) */
            else if (WIFSIGNALED(input_variables->status) && WTERMSIG(input_variables->status) == SIGINT)
                input_variables->status = 130;

            return 0; /* Return 0 to indicate successful execution */
        }

        /* If execution reaches here, there was an issue with executing the command */
        input_variables->status = 127;
        return 1; /* Return 1 to indicate execution failure */
    }
    else /* If access to the command is not permitted */
    {
        _error(input_variables, ": Permission denied\n"); /* Call the error handling function */
        input_variables->status = 126;
    }

    return 0; /* Return 0 to indicate successful completion (even if permission denied) */
}

/**
 * str_path - finds the PATH variable
 * @env_arr: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *str_path(char **env_arr)
{
    /* The string we're looking for to identify the PATH variable */
    char *path_str = "PATH=";
    unsigned int x = 0, y;

    /* Loop through each element in the env_arr array using a while loop */
    while (env_arr[x] != NULL)
    {
        y = 0; /* Initialize y for the inner loop */

        /* Compare the characters of the path_str string and the current environment variable using a while loop */
        while (y < 5 && path_str[y] == env_arr[x][y])
        {
            y++; /* Move to the next character */
        }

        /* If the loop completed without breaking and y is 5, the first 5 characters match "PATH=" */
        if (y == 5)
            break; /* Break out of the outer loop as well */

        x++; /* Move to the next environment variable */
    }

    /* Return the environment variable where "PATH" was found */
    return (env_arr[x]);
}

/**
 * is_PATH - checks if the command is a part of a path
 * @is_PATH: name of the command
 *
 * Return: 1 on success, 0 on failure
 */
int is_PATH(char *name)
{
	unsigned int i;

	for (i = 0; name[i]; i++)
	{
		if (name[i] == '/')
			return (1);
	}
	return (0);
}
