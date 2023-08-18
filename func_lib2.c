#include "shell.h"

/**
 * _strdup - Returns a pointer to new memory allocated space containing a copy
 * @replica: String to be duplicated
 * Return: A pointer to the new duplicated string
 */
char *_strdup(char *replica)
{
    char *clone;
    int len = 0;
    int i = 0;

    if (replica == NULL)
        return (NULL);

    while (replica[len])
        len++;

    clone = malloc(sizeof(char) * (len + 1));
    if (clone == NULL)
    {
        perror("Memory allocation error");
        return (NULL);
    }

    while (i < len)  // Changed i <= len to i < len
    {
        clone[i] = replica[i];
        i++;
    }
    clone[i] = '\0';  // Add null-terminator at the end of the cloned string
    return (clone);
}

/**
 * int_to_string - Converts an unsigned int to a string format
 * @count: Unsigned int to convert
 *
 * Return: Pointer to the converted string
 */
char *int_to_string(unsigned int count)
{
    char *str;
    unsigned int temp, digit;

    temp = count;
    /* Storing numbers in reverse in memory */
    for (digit = 0; temp != 0; digit++)
        temp /= 10;
    str = malloc(sizeof(char) * (digit + 1));
    if (str == NULL)
    {
        perror("Memory allocation error");
        exit(127);
    }
    str[digit] = '\0';

    /* Reversing the array to get the true figure */
    for (--digit; count; --digit)
    {
        str[digit] = (count % 10) + '0';
        count /= 10;
    }
    return (str);
}
