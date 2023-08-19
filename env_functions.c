#include "shell.h"

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
void env_plus(shell_t *shell_vars)
{
    unsigned int i = 0;
    char **plus;

    while (shell_vars->env_vars[i] != NULL)
        i++;

    unsigned int spec_elements = i + 2;

    plus = malloc(sizeof(char *) * spec_elements);
    if (!plus)
    {
        print_error(shell_vars, NULL);
        shell_vars->close_status = 127;
        _close(shell_vars);
    }

    unsigned int j = 0;
    while (j < i)
    {
        plus[j] = shell_vars->env_vars[j];
        j++;
    }

    plus[i] = new_env(shell_vars->tokens[1], shell_vars->tokens[2]);
    if (!plus[i])
    {
        print_error(shell_vars, NULL);
        free(shell_vars->cmd_mem);
        free(shell_vars->env_vars);
        free(shell_vars->tokens);
        env_free(shell_vars->env_vars);
        free(plus);
        exit(127);
    }

    plus[spec_elements - 1] = NULL;

    env_free(shell_vars->env_vars);
    shell_vars->env_vars = plus;
}
