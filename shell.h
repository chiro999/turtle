#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

#define UNUSED(x) (void)(x)

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(input_t *);
} builtins_t;

ssize_t _puts(char *s);
char *_strdup(char *duplicate);
char *_strcat(char *dest, char *src);
unsigned int _strlen(char *s);

char **_realloc(char **ptr, size_t *size);

int _strncmp(char *s1, char *s2);

int _atoi(char *s);

void _printer(char *str);
char *_int_str(unsigned int count);

/* _strtok & tokenize: _strtok.c & tokenizer.c */
unsigned int matching(char c, const char *str);
char *_strtok(char *str, const char *delim);
char **tokenize(char *arguments, char *delimiter);

#endif /* _SHELL_H_ */
