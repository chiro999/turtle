/**
 * is_env - finds an environment variable
 * @env_var: array of environment variables
 * @path: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **is_env(char **env_var, char *path)
{
    unsigned int i = 0, j, path_len = _strlen(path); /* Declare variables for iteration and path length */

    /* Iterate through the array of environment variables */
    while (env_var[i])
    {
        j = 0; // Reset j for each iteration

        /* Iterate through the characters of the current environment variable */
        while (j < path_len && path[j] == env_var[i][j])
        {
            j++; // Move to the next character

            /* Check if the loop finished and the current character is '=' */
            if (j == path_len && env_var[i][j] == '=')
                return (&env_var[i]); /* Return the address of the matching environment variable */
        }
        i++; // Move to the next environment variable
    }

    return (NULL); /* Return NULL if no match is found */
}

/**
 * env_free - free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */
void env_free(char **env)
{
    unsigned int i = 0;

    /* Iterate through the environment variables and free each one */
    while (env[i])
    {
        free(env[i]); /* Free the memory allocated for the current environment variable */
        i++; // Move to the next environment variable
    }

    free(env); /* Free the memory allocated for the array of environment variables */
}

/**
 * env_copy - create a new environment array from the environment passed to main
 * @environ: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **env_copy(char **environ)
{
    char **copy = NULL;  /* Pointer to the new environment array */
    size_t i = 0;        /* Counter for loops */
    size_t len;          /* Length of the new environment array */

    /* Count the number of elements in the existing environment array */
    while (environ[i] != NULL)
        i++;

    len = i + 1;  /* Calculate the length of the new environment array */

    /* Allocate memory for the new environment array */
    copy = malloc(sizeof(char *) * len);
    if (!copy)  /* Using if (!copy) instead of if (copy == NULL) */
    {
        perror("Error");  /* Change the error message */
        exit(1);
    }

    /* Copy each string from the existing environment to the new environment */
    i = 0;  /* Reset the counter for copying */
    while (environ[i] != NULL)
    {
        copy[i] = _strdup(environ[i]);
        i++;
    }

    /* Add a NULL pointer to mark the end of the new environment array */
    copy[i] = NULL;

    return copy;  /* Return a pointer to the newly created environment array */
}

/**
 * new_env - create a new environment variable string
 * @name: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *new_env(char *name, char *value)
{
    unsigned int name_len, value_len, i, j;
    char *new_env;
    unsigned int combined_length;  /* Combined length of name, value, '=', separator, and null terminator */
    char separator = '=';  /* The separator character */

    /* Calculate the lengths of the name and value strings */
    name_len = _strlen(name);
    value_len = _strlen(value);

    /* Calculate the combined length of the new environment variable string */
    /* +2 is added for the separator and null terminator */
    combined_length = name_len + value_len + 2;  /* +2 because of separator and null character */

    /* Allocate memory for the new environment variable string */
    new_env = malloc(sizeof(char) * combined_length);
    if (!new_env)  /* Using if (!new_env) instead of if (new == NULL) */
        return (NULL);

    /* Copy the characters from the name string to the new string using a while loop */
    i = 0;  /* Initialize the counter */
    while (name[i] != '\0')
    {
        new_env[i] = name[i];
        i++;
    }

    /* Set the separator character between name and value */
    new_env[i] = separator;

    /* Increment i to position after the separator */
    i++;

    /* Copy the characters from the value string to the new string using a while loop */
    j = 0;  /* Initialize the counter */
    while (value[j] != '\0')
    {
        new_env[i + j] = value[j];
        j++;
    }

    /* Add the null terminator to the new string */
    new_env[i + j] = '\0';

    return (new_env);  /* Return a pointer to the new environment variable string */
}

/**
 * env_plus - create a new environment variable
 * @input_variables: pointer to struct of variables
 *
 * Return: void
 */
void env_plus(input_t *input_variables)
{
    unsigned int i = 0;
    char **new_env;

    /* Count the number of existing environment variables using a while loop */
    while (input_variables->env[i] != NULL)
        i++;

    /* Calculate the total number of elements needed (variables + new variable + NULL terminator) */
    unsigned int spec_elements = i + 2;

    /* Allocate memory for a new environment array with space for the specified elements */
    new_env = malloc(sizeof(char *) * spec_elements);
    if (!new_env)
    {
        print_error(input_variables, NULL);
        input_variables->status = 127;
        _exit_(input_variables);
    }

    /* Copy existing environment variables to the new array using a while loop */
    unsigned int j = 0;
    while (j < i)
    {
        new_env[j] = input_variables->env[j];
        j++;
    }

    /* Create a new environment variable and add it to the new array */
    new_env[i] = add_value(input_variables->tokens[1], input_variables->tokens[2]);
    if (!new_env[i])
    {
        print_error(input_variables, NULL);
        free(input_variables->buffer);
        free(input_variables->commands);
        free(input_variables->tokens);
        free_environ(input_variables->env);
        free(new_env);
        exit(127);
    }

    /* Set the last element of the new array to NULL to terminate the list */
    new_env[spec_elements - 1] = NULL;

    /* Free the old environment array and update it with the new array */
    free(input_variables->env);
    input_variables->env = new_env;
}
