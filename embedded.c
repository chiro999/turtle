/**
 * curr_env - prints the current environment
 * @input_vars: struct of variables
 * Return: void.
 */
void curr_env(input_t *input_vars)
{
    unsigned int i = 0;

    while (input_vars->new_env[i])
    {
        str_out(input_vars->new_env[i]);
        str_out("\n");
        i++;
    }

    input_vars->status = 0;
}

/**
 * create_edit_env - create a new environment variable, or edit an existing variable
 * @input_vars: pointer to struct of variables
 *
 * Return: void
 */

void create_edit_env(input_t *input_vars)
{
    char **env_var;
    char *input;

    /* Check if the required arguments are present using logical OR */
    if (!input_vars->tokens[1] || !input_vars->tokens[2])
    {
        _error(input_vars, ": Incorrect number of arguments\n");
        input_vars->status = 2; /* Set error status */
        return; /* Exit the function */
    }

    /* Find an existing environment variable */
    env_var = find_env(input_vars->env, input_vars->tokens[1]);

    if (!env_var) /* Variable doesn't exist, create a new one */
    {
        env_plus(input_vars); /* Add a new environment variable */
    }
    else /* Variable exists, update its value */
    {
        /* Add the new value and get the updated input string */
        input = add_value(input_vars->tokens[1], input_vars->tokens[2]);

        if (!input) /* Adding value failed */
        {
            _error(input_vars, NULL); /* Output an error message */
            /* Free allocated memory and exit */
            free(input_vars->buffer);
            free(input_vars->commands);
            free(input_vars->tokens);
            free_environ(input_vars->env);
            exit(127); /* Exit with an error status code */
        }

        /* Free the old value and update with the new value */
        free(*env_var);
        *env_var = input;
    }

    input_vars->status = 0; /* Set success status */
}

/**
 * rm_env - remove an environment variable
 * @input_vars: pointer to a struct of variables
 *
 * Return: void
 */
void rm_env(input_t *input_vars)
{
    char **env, **new;

    unsigned int i, j;

    /* Find the environment variable to unset */
    env = find_env(input_vars->env, input_vars->tokens[1]);

    if (!env)
    {
        _error(input_vars, ": No variable to unset");
        return;
    }

    i = 0;
    while (input_vars->env[i] != NULL)
    {
        i++;
    }

    /* Allocate memory for the new environment array */
    new = malloc(sizeof(char *) * i);

    if (!new)
    {
        _error(input_vars, NULL);
        input_vars->status = 127;
        _exit_(input_vars); // Assuming _exit_ is a custom function
    }

    /* Copy environment variables except the one to unset */
    i = 0;
    while (input_vars->env[i] != *env)
    {
        new[i] = input_vars->env[i];
        i++;
    }

    j = i + 1;
    while (input_vars->env[j] != NULL)
    {
        new[i] = input_vars->env[j];
        i++;
        j++;
    }

    new[i] = NULL;
    free(*env);
    free(input_vars->env);
    input_vars->env = new;
    input_vars->status = 0;

}

/*
 * embedded - Checks if the command is a built-in and executes the corresponding function.
 * @inputs: Variables struct containing input data
 * Return: Pointer to the executed function or NULL
 */
void (*embedded(input_t *inputs))(input_t *inputs)
{
    unsigned int i = 0;

    builtins_t is_embedded[] = {
        {"setenv", create_edit_env},
        {"exit", close},
        {"env", curr_env},
        {"unsetenv", _unsetenv},
        {NULL, NULL}
    };

    while (is_embedded[i].f != NULL)
    {
        if (_strncmp(inputs->tokens[0], is_embedded[i].name) == 0)
            break;
        i++;
    }

    if (is_embedded[i].f != NULL)
        is_embedded[i].f(inputs);

    return (is_embedded[i].f);
}
