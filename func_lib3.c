#include "shell.h"

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



