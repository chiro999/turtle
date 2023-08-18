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
<<<<<<< HEAD
            print_error(shell_vars, "Fork failed\n");
=======
            print_error(shell_vars, NULL); /* Call the error handling function */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972

        if (child_process == 0)
        {
<<<<<<< HEAD
            if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
                print_error(shell_vars, "Execution failed\n");
=======
            /* Attempt to execute the command using execve() */
            if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
                _error(input_variables, NULL); /* Call the error handling function */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
        }
        else
        {
<<<<<<< HEAD
            wait(&shell_vars->close_status);

            if (WIFEXITED(shell_vars->close_status))
                shell_vars->close_status = WEXITSTATUS(shell_vars->close_status);
            else if (WIFSIGNALED(shell_vars->close_status) && WTERMSIG(shell_vars->close_status) == SIGINT)
                shell_vars->close_status = 130;

            return 0;
=======
            /* Wait for the child process to complete */
            wait(&shell_vars->close_status);

            /* Check if the child process exited normally */
            if (WIFEXITED(shell_vars->close_status))
                shell_vars->close_status = WEXITSTATUS(shell_vars->close_status);
            /* Check if the child process was terminated by a signal (e.g., Ctrl+C) */
            else if (WIFSIGNALED(shell_vars->close_status) && WTERMSIG(shell_vars->close_status) == SIGINT)
                shell_vars->close_status = 130;

            return 0; /* Return 0 to indicate successful execution */
        }

        /* If execution reaches here, there was an issue with executing the command */
        shell_vars->close_status = 127;
        return 1; /* Return 1 to indicate execution failure */
    }
    else /* If access to the command is not permitted */
    {
        print_error(shell_vars, ": Permission denied\n"); /* Call the error handling function */
        shell_vars->close_status = 126;
    }

    return 0; /* Return 0 to indicate successful completion (even if permission denied) */
}

/**
 * str_path - finds the PATH variable
 * @env_arr: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *str_path(char **env_vars)
{
    /* The string we're looking for to identify the PATH variable */
    char *path_str = "PATH=";
    unsigned int x = 0, y;

    /* Loop through each element in the env_arr array using a while loop */
    while (env_vars[x] != NULL)
    {
        y = 0; /* Initialize y for the inner loop */

        /* Compare the characters of the path_str string and the current environment variable using a while loop */
        while (y < 5 && path_str[y] == env_vars[x][y])
        {
            y++; /* Move to the next character */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
        }

        shell_vars->close_status = 127;
        return 1;
    }
<<<<<<< HEAD
    else
    {
        print_error(shell_vars, "Permission denied\n");
        shell_vars->close_status = 126;
    }

    return 0;
=======

    /* Return the environment variable where "PATH" was found */
    return (env_vars[x]);
}

/*
 * exec_curr_dir - Execute a command from the current working directory
 * @input_variables: Input structure containing command tokens and environment variables
 *
 * This function checks if the specified command exists in the current working directory.
 * If the command exists and is executable, a child process is forked to execute it using execve.
 * The parent process waits for the child to finish and handles the exit status accordingly.
 * If the command is not found or cannot be executed, error messages are displayed and
 * the status in the input structure is set appropriately.
 *
 * Return: 0 if the function completes successfully, 1 if there's an error
 */
int exec_curr_dir(shell_t *shell_vars)
{
    pid_t child_process;

    /* Check if the command file exists in the current working directory */
    if (access(shell_vars->tokens[0], F_OK) == 0)
    {
        /* Check if the command file is executable */
        if (access(shell_vars->tokens[0], X_OK) == 0)
        {
            /* Fork a child process to execute the command */
            child_process = fork();

            if (child_process == -1)
               print_error(shell_vars, NULL); /* Handle error */

            if (child_process == 0) /* Child process */
            {
                /* Execute the command using execve */
                if (execve(shell_vars->tokens[0], shell_vars->tokens, shell_vars->env_vars) == -1)
                   print_error(shell_vars, NULL); /* Handle error */
            }
            else /* Parent process */
            {
                /* Wait for the child process to finish */
                wait(&shell_vars->close_status);

                /* Check exit status of the child process */
                if (WIFEXITED(shell_vars->close_status))
                    shell_vars->close_status = WEXITSTATUS(shell_vars->close_status);
                else if (WIFSIGNALED(shell_vars->close_status) && WTERMSIG(shell_vars->close_status) == SIGINT)
                    shell_vars->close_status = 130;

                return 0; /* Exit the function */
            }

            /* If execve or fork failed, set the status and return */
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

    /* If the command is not found, set the status and return */
    print_error(shell_vars, ": not found\n");
    shell_vars->close_status = 127;
    return 0;
}

/* 
 * check_path - Execute command via PATH
 * @inputs: Input structure with tokens, env vars, and status
 *
 * Searches command using PATH. Checks current dir, then PATH dirs. Executes if found,
 * sets status if not.
 */
void check_path(shell_t *shell_vars)
{
    char *path, *clone = NULL, *check = NULL;
    unsigned int i = 0;
    int exec_success = 0; /* Indicates whether the command execution was successful */
    char **path_tokens;

    /* Check if the command is in the current working directory */
    if (is_PATH(shell_vars->tokens[0]))
        exec_success = exec_curr_dir(shell_vars);
    else
    {
        /* Find the PATH environment variable */
        path = str_path(shell_vars->env_vars);

        if (path != NULL)
        {
            /* Duplicate and tokenize the PATH for searching */
            clone = _strdup(path + 5);
            path_tokens = custom_tokenizer(clone, ":");

            /* Loop through directories to find and execute the command using while loops */
            i = 0;
            while (path_tokens && path_tokens[i])
            {
                check = _strcat(path_tokens[i], shell_vars->tokens[0]);

                /* Check if the executable exists in the directory */
                int exists = access(check, F_OK);
                if (exists == 0)
                {
                    exec_success = _execute(check, shell_vars);
                    free(check);
                    break;
                }

                free(check);
                i++;
            }

            /* Clean up allocated memory */
            free(clone);
            if (path_tokens == NULL)
            {
                shell_vars->close_status = 127;
                _close(shell_vars);
            }
        }

        /* If executable not found in any directory */
        if (path == NULL || path_tokens[i] == NULL)
        {
            print_error(shell_vars, ": not found\n");
            shell_vars->close_status = 127;
        }

        /* Clean up allocated memory */
        free(path_tokens);
    }

    /* If execution is successful, exit the program */
    if (exec_success == 1)
        _close(shell_vars);
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
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
}
