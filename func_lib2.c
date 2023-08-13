#include "shell.h"

/**
 * str_write - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t str_write(char *str)
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
