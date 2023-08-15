#include "shell.h"

/**
 * _error - prints error messages to standard error
 * @inputs: pointer to struct of variables
 * @message: message to print
 *
 * Return: void
 */
void print_error(input_variables *inputs, char *err_message)
{
	char *_argc;

	/* Print program name */
	str_error(inputs->argv[0]);
	str_error(": ");

	/* Convert and print command count */
	_argc = _int_str(inputs->count);
	str_error(_argc);
	free(_argc);
	str_error(": ");

	/* Print command name */
	str_error(inputs->tokens[0]);

	/* Print custom error message or system error message */
	if (err_message)
	{
		str_error(err_message);
	}
	else
		perror("");
}
