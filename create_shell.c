#include "shell.h"

/**
 * handle_signal - handles ^C signal interupt
 * @handle_signal: signal handle parameter
 *
 * Return: void
 */
void handle_signal(int handle_signal)
{
    (void) handle_signal;
    str_out("\n$ ");
    fflush(stdout);
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @arg_arr: array of arguments passed to main
 * @e_vars: array of environment variables
 *
 * Return: 0 or exit close_status, or ?
 */
int main(int argc, char **arg_arr, char **e_vars)
{
    size_t cmd_mem = 0;
    unsigned int interactive_mode = 0, i;
    shell_t shell_vars = {NULL, NULL, NULL, 0, NULL, NULL, 0};

    UNUSED(argc);

    shell_vars.argv = arg_arr;
    shell_vars.env_vars = env_copy(e_vars);
    signal(SIGINT, handle_signal);
    if (!isatty(STDIN_FILENO))
        interactive_mode = 1;
    if (interactive_mode == 0)
        str_out("$ ");

    while (getline(&(shell_vars.cmd_mem), &cmd_mem, stdin) != -1)
    {
        shell_vars.tokenCount++;
        shell_vars.commands = custom_tokenizer(shell_vars.cmd_mem, ";");

        i = 0;
        while (shell_vars.commands && shell_vars.commands[i] != NULL)
        {
            shell_vars.tokens = custom_tokenizer(shell_vars.commands[i], "\n \t\r");
            if (shell_vars.tokens && shell_vars.tokens[0])
            {
                if (embedded(&shell_vars) == NULL)
                    path_check(&shell_vars);
            }
            free(shell_vars.tokens);
            i++;
        }

        free(shell_vars.cmd_mem);
        free(shell_vars.commands);
        if (interactive_mode == 0)
            str_out("$ ");
        shell_vars.cmd_mem = NULL;
    }

    if (interactive_mode == 0)
        str_out("\n");
    env_free(shell_vars.env_vars);
    free(shell_vars.cmd_mem);
    exit(shell_vars.close_status);
}
