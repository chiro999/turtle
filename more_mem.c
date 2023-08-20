#include "shell.h"

/**
 * more_mem - reallocates a pointer to increase the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **more_mem(char **ptr, size_t *size)
{
	char **new;
	size_t i = 0;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	/* copy elements of old array into new array */
	while (i < (*size))
	{
		new[i] = ptr[i];
		i++;
	}
	*size += 10;
	free(ptr);
	return (new);
}
