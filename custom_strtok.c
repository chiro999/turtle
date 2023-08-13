User
#include "shell.h"

/**
 * matching - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int matching(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

char *_strtok(char *str, const char *delim)
{
    static char *token;
    static char *next;
    unsigned int i;

    /* Initialize 'next' with 'str' if provided */
    if (str != NULL)
        next = str;

    /* Store the current value of 'next' in 'token' */
    token = next;

    /* If 'token' is NULL, there are no more tokens, so return NULL */
    if (token == NULL)
        return (NULL);

    /* Find the start of the next token by skipping over delimiter characters */
    for (i = 0; next[i] != '\0'; i++)
    {
        if (matching(next[i], delim) == 0)
            break;
    }

    /* If the end of the string or a '#' character is found, there are no more tokens */
    if (next[i] == '\0' || next[i] == '#')
    {
        next = NULL;
        return (NULL);
    }

    /* Update 'token' to point to the beginning of the next token */
    token = next + i;
    next = token;

    /* Find the end of the token by searching for the next delimiter */
    for (i = 0; next[i] != '\0'; i++)
    {
        if (matching(next[i], delim) == 1)
            break;
    }

    /* If the end of the string is reached, set 'next' to NULL */
    if (next[i] == '\0')
        next = NULL;
    else
    {
        /* Replace the delimiter character with a null terminator */
        next[i] = '\0';

        /* Update 'next' to point to the character after the delimiter */
        next = next + i + 1;

        /* If the next character is the end of the string, set 'next' to NULL */
        if (*next == '\0')
            next = NULL;
    }

    /* Return a pointer to the current token */
    return (token);
}
