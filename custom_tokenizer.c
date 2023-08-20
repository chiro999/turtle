#include "shell.h"

/**
 * custom_tokenizer - Tokenizes a given buffer based on a delimiter
 * @inputBuffer: The buffer to be tokenized
 * @delimiter: The delimiter used for tokenization
 *
 * Returns: An array of pointers to the tokens
 */
char **custom_tokenizer(char *inputBuffer, char *delimiter)
{
    char **tokens = NULL;  /* Array of pointers to hold tokens */
    size_t index = 0, tokenCount = 10;  /* Index and initial token count */

    if (inputBuffer == NULL)
        return NULL;

    /* Allocate memory for the token array */
    tokens = malloc(sizeof(char *) * tokenCount);
    if (tokens == NULL)
    {
        perror("Fatal Error");
        return NULL;
    }

    char *token = strtok(inputBuffer, delimiter);
    while (token != NULL)
    {
        tokens[index] = token;
        index++;

        if (index == tokenCount)
        {
            /* Resize the token array using a custom resizing function */
            tokens = more_mem(tokens, &tokenCount);
            if (tokens == NULL)
            {
                perror("Fatal Error");
                return NULL;
            }
        }

        token = strtok(NULL, delimiter);
    }

    tokens[index] = NULL; 
    return tokens;
}
