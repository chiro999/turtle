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
