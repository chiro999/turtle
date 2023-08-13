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

/**
 * int_to_string - converts an unsigned int to a string format
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *int_to_string(unsigned int count)
{
	char *str;
	unsigned int temp, digit;

	temp = count;
	/*storing numbers in reverse in memory*/
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	str = malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
	{
		perror("Abandon Ship!!");
		exit(127);
	}
	str[digit] = '\0';

	/* reversing the array to get the true figure */
	for (--digit; count; --digit)
	{
		str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (str);
}
