#include "shell.h"

/**
 * _strdup - returns pointer to new mem alloc space which contains copy
 * @replica: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *_strdup(char *replica)
{
	char *clone;
	int len = 0;
	int i = 0;

	if (replica == 0)
		return (NULL);

	while(replica[len])
		len++;
		
	clone = malloc(sizeof(char) * (len + 1));

	while(i <= len)
	{
		clone[i] = replica[i];
		i++;
	}
	return (clone);
}
