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
    while (shell_vars->tokens[i] != NULL)
    {
        if (_strncmp(shell_vars->tokens[i], "exit") == 0 && shell_vars->tokens[i + 1] != NULL)
        {
            i++; // Move to the next token
            close_status = _atoi(shell_vars->tokens[i]); /* Convert the exit status string to an integer */

            /* Check if the conversion failed (non-numeric input) */
            if (close_status == -1)
            {
                shell_vars->close_status = 2; /* Set exit status to 2 (indicating an error) */
                print_error(shell_vars, ": Unacceptable input: "); /* Call the error handling function */
                str_out(shell_vars->tokens[i]); /* Print the problematic input */
                str_out("\n"); /* Print a newline character */
                free(shell_vars->commands); /* Free allocated memory */
                shell_vars->commands = NULL; /* Set pointer to NULL */
                return; /* Exit the function */
            }

            shell_vars->close_status = close_status; /* Set the exit status to the provided status */
        }
        i++; // Move to the next token
    }

    /* Free allocated memory */
    free(shell_vars->cmd_mem);
    free(shell_vars->tokens);
    free(shell_vars->commands);
    env_free(shell_vars->env_vars);

    exit(shell_vars->close_status); /* Exit the program with the specified exit status */
}
