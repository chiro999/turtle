#include "shell.h"

/**
 * curr_env - prints the current environment
 * @input_vars: struct of variables
 * Return: void.
 */
void curr_env(shell_t *shell_vars)
{
    unsigned int i = 0;

    while (shell_vars->env_vars[i])
    {
        str_out(shell_vars->env_vars[i]);
        str_out("\n");
        i++;
    }

    shell_vars->close_status = 0;
}

/**
 * create_edit_env - create a new environment variable, or edit an existing variable
 * @input_vars: pointer to struct of variables
 *
 * Return: void
 */

void create_edit_env(shell_t *shell_vars)
{
    char **env_var;
    char *input;

    /* Check if the required arguments are present using logical OR */
    if (!shell_vars->tokens[1] || !shell_vars->tokens[2])
    {
        print_error(shell_vars, ": Incorrect number of arguments\n");
        shell_vars->close_status = 2; /* Set error status */
        return; /* Exit the function */
    }

    /* Find an existing environment variable */
    env_var = is_env(shell_vars->env_vars, shell_vars->tokens[1]);

    if (!env_var) /* Variable doesn't exist, create a new one */
    {
        env_plus(shell_vars); /* Add a new environment variable */
    }
    else /* Variable exists, update its value */
    {
        /* Add the new value and get the updated input string */
        input = new_env(shell_vars->tokens[1], shell_vars->tokens[2]);

        if (!input) /* Adding value failed */
        {
            print_error(shell_vars, NULL); /* Output an error message */
            /* Free allocated memory and exit */
            free(shell_vars->cmd_mem);
            free(shell_vars->commands);
            free(shell_vars->tokens);
            env_free(shell_vars->env_vars);
            exit(127); /* Exit with an error status code */
        }

        /* Free the old value and update with the new value */
        free(*env_var);
        *env_var = input;
    }

    shell_vars->close_status = 0; /* Set success status */
}

/**
 * rm_env - remove an environment variable
 * @input_vars: pointer to a struct of variables
 *
 * Return: void
 */
void rm_env(shell_t *shell_vars)
{
    char **env, **new;

    unsigned int i, j;

    /* Find the environment variable to unset */
    env = is_env(shell_vars->env_vars, shell_vars->tokens[1]);

    if (!env)
    {
        print_error(shell_vars, ": No variable to unset");
        return;
    }

    i = 0;
    while (shell_vars->env_vars[i] != NULL)
    {
        i++;
    }

    /* Allocate memory for the new environment array */
    new = malloc(sizeof(char *) * i);

    if (!new)
    {
        print_error(shell_vars, NULL);
        shell_vars->close_status = 127;
        _close(shell_vars); // Assuming _exit_ is a custom function
    }

    /* Copy environment variables except the one to unset */
    i = 0;
    while (shell_vars->env_vars[i] != *env)
    {
        new[i] = shell_vars->env_vars[i];
        i++;
    }

    j = i + 1;
    while (shell_vars->env_vars[j] != NULL)
    {
        new[i] = shell_vars->env_vars[j];
        i++;
        j++;
    }

    new[i] = NULL;
    free(*env);
    free(shell_vars->env_vars);
    shell_vars->env_vars = new;
    shell_vars->close_status = 0;

}

/*
 * embedded - Checks if the command is a built-in and executes the corresponding function.
 * @inputs: Variables struct containing input data
 * Return: Pointer to the executed function or NULL
 */
void (*embedded(shell_t *shell_vars))(shell_t *shell_vars)
{
    unsigned int i = 0;

    embedded_t is_embedded[] = {
        {"edit", create_edit_env},
        {"X", _close},
        {"current", curr_env},
        {"remove", rm_env},
        {NULL, NULL}
    };

    while (is_embedded[i].f != NULL)
    {
        if (_strcmp(shell_vars->tokens[0], is_embedded[i].name) == 0)
            break;
        i++;
    }

    if (is_embedded[i].f != NULL)
        is_embedded[i].f(shell_vars);

    return (is_embedded[i].f);
}
