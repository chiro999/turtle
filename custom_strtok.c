User
#include "shell.h"

/**
 * is_a_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int is_a_match(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

char *custom_strtok(char *str, const char *delim)
{
    static char *token;
    static char *next_token;
    unsigned int i;

    /* Initialize 'next_token' with 'str' if provided */
    if (str != NULL)
        next_token = str;

    /* Store the current value of 'next_token' in 'token' */
    token = next_token;

    /* If 'token' is NULL, there are no more tokens, so return NULL */
    if (token == NULL)
        return (NULL);

    /* Find the start of the next token by skipping over delimiter characters */
    for (i = 0; next_token[i] != '\0'; i++)
    {
        if (is_a_match(next_token[i], delim) == 0)
            break;
    }

    /* If the end of the string or a '#' character is found, there are no more tokens */
    if (next_token[i] == '\0' || next_token[i] == '#')
    {
        next_token = NULL;
        return (NULL);
    }

    /* Update 'token' to point to the beginning of the next token */
    token = next_token + i;
    next_token = token;

    /* Find the end of the token by searching for the next delimiter */
    for (i = 0; next_token[i] != '\0'; i++)
    {
        if (is_a_match(next_token[i], delim) == 1)
            break;
    }

    /* If the end of the string is reached, set 'next' to NULL */
    if (next_token[i] == '\0')
        next_token = NULL;
    else
    {
        /* Replace the delimiter character with a null terminator */
        next_token[i] = '\0';

        /* Update 'next' to point to the character after the delimiter */
        next_token += i + 1;

        /* If the next character is the end of the string, set 'next' to NULL */
        if (*next_token == '\0')
            next_token = NULL;
    }

    /* Return a pointer to the current token */
    return (token);
}
