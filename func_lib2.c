#include "shell.h"

/**
 * str_out - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t str_out(char *str)
{
	ssize_t count, out_count;

	count = _strlen(str);
	out_count = write(STDOUT_FILENO, str, count);
	if (out_count != count)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (out_count);
}

/**
 * _strlen - returns the length of a string
 * @s: string to evaluate
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int x;

	x = 0;

	while (s[x] != '\0')
	{
		x++;
	}

	return (x);
}

/**
 * str_err - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void str_error(char *str)
{
	ssize_t count, err_count;

	count = _strlen(str);
	err_count = write(STDERR_FILENO, str, count);
	if (err_count != count)
	{
		perror("Fatal Error");
		exit(1);
	}

}

