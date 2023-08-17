/**
 * curr_env - prints the current environment
 * @input_vars: struct of variables
 * Return: void.
 */
void curr_env(input_t *input_vars)
{
    unsigned int i = 0;

    while (input_vars->new_env[i])
    {
        str_out(input_vars->new_env[i]);
        str_out("\n");
        i++;
    }

    input_vars->status = 0;
}
