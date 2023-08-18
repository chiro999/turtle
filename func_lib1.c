#include "shell.h"

/**
 * _strcat - Concatenates two strings
 * @dest: String to append to
 * @src: String to add
 *
 * Return: A pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
    int x = 0, y = 0;

    while (dest[x] != '\0')
        x++;

    while (src[y] != '\0')
    {
        dest[x] = src[y];
        y++;
        x++;
    }

    dest[x] = '\0';

    return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string to compare
 * @s2: Second string to compare
 *
 * Return: Negative value if s1 is less than s2,
 *         0 if they're equal,
 *         Positive value if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 == *s2)
    {
        if (*s1 == '\0')
            return (0);

        s1++;
        s2++;
    }

    return (*s1 - *s2);
}

/**
 * _atoi - Converts a string to an integer
 * @s: The string to convert
 *
 * Return: The converted integer
 */
int _atoi(char *s)
{
    int c = 0;
    int sign = 1;
    unsigned int sum = 0;
    int final = 0;

    while (s[c] != '\0')
    {
        if (s[c] == '-')
            sign *= -1;
        else if (s[c] >= '0' && s[c] <= '9')
            break;
        c++;
    }

    while (s[c] >= '0' && s[c] <= '9')
    {
        sum = sum * 10 + (s[c] - '0');
        c++;
    }

    if (sign == -1)
        final = -sum;
    else
        final = sum;

    return (final);
}
