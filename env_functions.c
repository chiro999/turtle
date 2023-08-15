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
