#include "shell.h"

/**
 * mem_alloc - reallocates a pointer to increase the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **(char **ptr, size_t *size)
{
	char **new;
	size_t i = 0;

	new = malloc(sizeof(char *) * ((*size) + 20));
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
	*size += 20;
	free(ptr);
	return (new);
}
