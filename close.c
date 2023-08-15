#include "shell.h"

/**
 * close - Exit the program
 * @input_variables: Pointer to input variables
 * Return: void
 */
void close(input_t *input_variables)
{
    int close_status; /* Declare a variable to store the exit status */
    int i = 0;

    /* Look for the "exit" command and check if an exit status is provided */
    while (input_variables->tokens[i] != NULL)
    {
        if (_strncmp(input_variables->tokens[i], "exit") == 0 && input_variables->tokens[i + 1] != NULL)
        {
            i++; // Move to the next token
            close_status = _atoi(input_variables->tokens[i]); /* Convert the exit status string to an integer */

            /* Check if the conversion failed (non-numeric input) */
            if (close_status == -1)
            {
                input_variables->status = 2; /* Set exit status to 2 (indicating an error) */
                _error(input_variables, ": Unacceptable input: "); /* Call the error handling function */
                str_out(input_variables->tokens[i]); /* Print the problematic input */
                str_out("\n"); /* Print a newline character */
                free(input_variables->commands); /* Free allocated memory */
                input_variables->commands = NULL; /* Set pointer to NULL */
                return; /* Exit the function */
            }

            input_variables->status = close_status; /* Set the exit status to the provided status */
        }
        i++; // Move to the next token
    }

    /* Free allocated memory */
    free(input_variables->buffer);
    free(input_variables->tokens);
    free(input_variables->commands);
    free_environ(input_variables->env);

    exit(input_variables->status); /* Exit the program with the specified exit status */
}
