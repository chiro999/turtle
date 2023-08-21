#include "shell.h"

/**
 * more_mem - reallocates a pointer to increase the space
 * @old_arr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **more_mem(char **old_arr, size_t *size)
{
	char **new_arr;
	size_t i = 0;

	new_arr = malloc(sizeof(char *) * ((*size) + 10));
	if (!new_arr)
	{
		free(old_arr);
		return (NULL);
	}
	/* copy elements of old array into new array */
	while (i < (*size))
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	*size += 10;
	free(old_arr);
	return (new_arr);
}
