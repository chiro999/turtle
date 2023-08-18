#include "shell.h"

/**
 * print_error - Prints error messages to standard error
 * @shell_vars: Pointer to struct of variables
 * @err_message: Message to print
 *
 * Return: void
 */
void print_error(shell_t *shell_vars, char *err_message)
{
    char *tokenCount;

    /* Print program name */
    str_error(shell_vars->argv[0]);
    str_error(": ");

    /* Convert and print command count */
<<<<<<< HEAD
    tokenCount = int_to_string(shell_vars->tokenCount);
    str_error(tokenCount);
=======
    tokenCount = int_to_str(shell_vars->tokenCount);
    str_error(tokenCpimt);
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
    free(tokenCount);
    str_error(": ");

    /* Print command name */
    str_error(shell_vars->tokens[0]);

    /* Print custom error message or system error message */
    if (err_message) {
        str_error(err_message);
    } else {
        perror(""); // Prints system error message
    }
}
