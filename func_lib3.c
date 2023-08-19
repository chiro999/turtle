#include "shell.h"

/**
 * _strdup - returns pointer to new mem alloc space which contains copy
 * @replica: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *_strdup(char *replica)
{
	char *clone;
	int len = 0;
	int i = 0;

	if (replica == 0)
		return (NULL);

	while(replica[len])
		len++;
		
	clone = malloc(sizeof(char) * (len + 1));

	while(i <= len)
	{
		clone[i] = replica[i];
		i++;
	}
	return (clone);
}

/**
 * int_to_string - converts an unsigned int to a string format
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *int_to_string(unsigned int count)
{
	char *str;
	unsigned int temp, digit;

	temp = count;
	/*storing numbers in reverse in memory*/
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	str = malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
	{
		perror("Abandon Ship!!");
		exit(127);
	}
	str[digit] = '\0';

	/* reversing the array to get the true figure */
	for (--digit; count; --digit)
	{
		str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (str);
}

/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: length of string
 */
unsigned int _strlen(char *s)
{
	unsigned int i;

	i = 0;

	while(s[i])
		i++;
		
	return (i);
}

/**
 * str_error - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void str_error(char *str)
{
	ssize_t num, string_len;

	num = _strlen(str);
	string_len = write(STDERR_FILENO, str, num);
	if (string_len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * str_out - writes a string to standard output
 * @s: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t str_out(char *s)
{
	ssize_t num, len;

	num = _strlen(s);
	len = write(STDOUT_FILENO, s, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}



