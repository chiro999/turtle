#include "shell.h"

/**
 * is_a_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int is_a_match(char y, const char *str)
{
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        if (y == str[i])
            return 1;

        i++;
    }

    return 0;
}

char *custom_strtok(char *str, const char *delim)
{
    static char *token;
    static char *next_token;
    unsigned int i;

    if (str != NULL)
        next_token = str;

    token = next_token;

    if (!token)
        return NULL;

    i = 0;
    while (token[i] != '\0' && is_a_match(token[i], delim) == 0)
        i++;

    if (token[i] == '\0')
    {
        next_token = NULL;
        return NULL;
    }

    token += i;

    i = 0;
    while (token[i] != '\0' && is_a_match(token[i], delim) == 1)
        i++;

    if (token[i] == '\0')
        next_token = NULL;
    else
    {
        token[i] = '\0';
        next_token = token + i + 1;

        if (*next_token == '\0')
            next_token = NULL;
    }

    return token;
}
