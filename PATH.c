/**
 * is_PATH - checks if the command is a part of a path
 * @is_PATH: name of the command
 *
 * Return: 1 on success, 0 on failure
 */
int check_dir(char *name)
{
	unsigned int i;

	for (i = 0; name[i]; i++)
	{
		if (name[i] == '/')
			return (1);
	}
	return (0);
}
