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
<<<<<<< HEAD
    char **tokens = NULL; 
    size_t index = 0, tokenCount = 10; 
=======
    char **tokens = NULL;  /* Array of pointers to hold tokens */
    size_t index = 0, tokenCount = 10;  /* Index and initial token count */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972

    if (inputBuffer == NULL)
        return NULL;  

<<<<<<< HEAD
=======
    /* Allocate memory for the token array */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
    tokens = malloc(sizeof(char *) * tokenCount);
    if (tokens == NULL)
    {
        perror("Fatal Error");
        return NULL;  
    }
<<<<<<< HEAD
 
    char *token = strtok(inputBuffer, delimiter);
    while (token != NULL)
=======

    /* Loop through the input buffer, tokenizing using the delimiter */
    while ((tokens[index] = custom_tokenizer(inputBuffer, delimiter)) != NULL)
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
    {
        tokens[index] = token;
        index++;  

        if (index == tokenCount)
        {
<<<<<<< HEAD
            tokens = more_mem(tokens, &tokenCount); 
            if (tokens == NULL)
=======
            /* Resize the token array using a custom resizing function */
            tokens = more_mem(tokens, &tokenCount);
            if (tokenArray == NULL)
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
            {
                perror("Fatal Error");
                return NULL;
            }
        }

        token = strtok(NULL, delimiter); 
    }

<<<<<<< HEAD
    tokens[index] = NULL;  
    return tokens; 
=======
    return tokens;  /* Return the array of tokens */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
}
