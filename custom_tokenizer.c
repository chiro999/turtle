#include "shell.h"  /* Including the necessary header file */

/**
 * CustomTokenizer - Tokenizes a given buffer based on a delimiter
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
        return NULL;  /* If the input buffer is NULL, return NULL */

    /* Allocate memory for the token array */
    tokens = malloc(sizeof(char *) * tokenCount);
    if (tokens == NULL)
    {
        perror("Fatal Error");
        return NULL;  /* If memory allocation fails, return NULL */
    }

    /* Loop through the input buffer, tokenizing using the delimiter */
    while ((tokens[index] = custom_tokenizer(inputBuffer, delimiter)) != NULL)
    {
        index++;  /* Increment the index for each successfully tokenized element */

        /* Check if the current index exceeds the current token count */
        if (index == tokenCount)
        {
            /* Resize the token array using a custom resizing function */
            tokens = more_mem(tokens, &tokenCount);
            if (tokenArray == NULL)
            {
                perror("Fatal Error");
                return NULL;  /* If resizing fails, return NULL */
            }
        }

        inputBuffer = NULL;  /* Reset the input buffer for subsequent tokenization */
    }

    return tokens;  /* Return the array of tokens */
}
