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
 * struct input - variables
 * @tokens: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: commands to execute
 */
typedef struct shell_vars
{
	char **tokens;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} shell_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct embedded
{
	char *name;
	void (*f)(input_t *);
} embedded_t

/* PATH functions */
int _execute(char *command, input_t *input_variables);
char *str_path(char **env_arr);
exec_curr_dir(input_t *input_variables);
void check_path(input_t *inputs);
int is_PATH(char *name);

/* close function */
void close(input_t *input_variables);

/* strtok functions */
unsigned int is_a_match(char c, const char *str)
char *custom_strtok(char *str, const char *delim)

/* tokenizer function */
char **custom_tokenizer(char *inputBuffer, char *delimiter)

/* embedded functions */
void curr_env(input_t *input_vars);
void create_edit_env(input_t *input_vars);
void rm_env(input_t *input_vars);
void (*embedded(input_t *inputs))(input_t *inputs);

/* environment function */
char **is_env(char **env_var, char *path);
void env_free(char **env);
char **env_copy(char **environ);
char *new_env(char *name, char *value);
void env_plus(input_t *input_variables);

/* stdlib replacements */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

ssize_t str_out(char *str);
int _strlen(char *s);
void str_error(char *str);

char *_strdup(char *replica)
char *int_to_string(unsigned int count)

/* memory reallocation function */
char **more_mem(char **ptr, size_t *size);

/*print error function*/
void print_error(input_variables *input_variables, char *err_message);

/* main function yet to be added */
void sig_handler(int sig_handler);
int main(int argc, char **argv, char **environment);

#endif /* _SHELL_H_ */
