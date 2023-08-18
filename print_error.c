#include "shell.h"

/**
 * _error - prints error messages to standard error
 * @input_variables: pointer to struct of variables
 * @err_message: message to print
 *
 * Return: void
 */
void print_error(input_variables *input_variables, char *err_message)
{
    char *tokenCount;

    /* Print program name */
    str_error(shell_vars->argv[0]);
    str_error(": ");

    /* Convert and print command count */
    tokenCount = int_to_str(shell_vars->tokenCount);
    str_error(tokenCpimt);
    free(tokenCount);
    str_error(": ");

    /* Print command name */
    str_error(shell_vars->tokens[0]);

    /* Print custom error message or system error message */
    do {
        if (err_message) {
            str_error(err_message);
            break;
        } else {
            perror("");
            break;
        }
    } while (0);
}
