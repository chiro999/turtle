#include <stddef.h>
#include <stdlib.h>

/**
 * is_env - finds an environment variable
 * @env_var: array of environment variables
 * @path: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **is_env(char **env_var, char *path)
{
    unsigned int i = 0, j, path_len = _strlen(path);

    while (env_var[i])
    {
        j = 0;

        while (path[j] != '\0' && path[j] == env_var[i][j])
        {
            j++;
        }

        if (path[j] == '\0' && env_var[i][j] == '=')
            return (&env_var[i]);

        i++;
    }

    return (NULL);
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

    while (env[i])
    {
        free(env[i]);
        i++;
    }

    free(env);
}

/**
 * env_copy - create a new environment array from the environment passed to main
 * @environ: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **env_copy(char **environ)
{
    char **copy = NULL;
    size_t i = 0, len;

    while (environ[i] != NULL)
        i++;

    len = i + 1;

    copy = malloc(sizeof(char *) * len);
    if (!copy)
    {
        perror("Memory Allocation Error");
        exit(1);
    }

    i = 0;
    while (environ[i] != NULL)
    {
        copy[i] = _strdup(environ[i]);
        i++;
    }

    copy[i] = NULL;

    return copy;
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
    unsigned int name_len, value_len, i = 0, j = 0;
    char *new_env;
    unsigned int combined_length;
    char separator = '=';

    name_len = _strlen(name);
    value_len = _strlen(value);

    combined_length = name_len + value_len + 2;

    new_env = malloc(sizeof(char) * combined_length);
    if (!new_env)
        return NULL;

    while (i < name_len)
    {
        new_env[i] = name[i];
        i++;
    }

    new_env[i] = separator;

    i++;

    while (j < value_len)
    {
        new_env[i + j] = value[j];
        j++;
    }

    new_env[i + j] = '\0';

    return new_env;
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

    while (input_variables->env[i] != NULL)
        i++;

    unsigned int spec_elements = i + 2;

    new_env = malloc(sizeof(char *) * spec_elements);
    if (!new_env)
    {
        print_error(input_variables, NULL);
        input_variables->status = 127;
        _exit_(input_variables);
    }

    unsigned int j = 0;
    while (j < i)
    {
        new_env[j] = input_variables->env[j];
        j++;
    }

    new_env[i] = new_env(input_variables->tokens[1], input_variables->tokens[2]);
    if (!new_env[i])
    {
        print_error(input_variables, NULL);
        free(input_variables->buffer);
        free(input_variables->commands);
        free(input_variables->tokens);
        env_free(input_variables->env);
        free(new_env);
        exit(127);
    }

    new_env[spec_elements - 1] = NULL;

    env_free(input_variables->env);
    input_variables->env = new_env;
}