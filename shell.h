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
	char *cmd_mem;
	char **env_vars;
	size_t tokenCount;
	char **argv;
	int close_status;
	char **commands;
} shell_t;

/**
 * struct shell_vars - Variables for the shell
 * @tokens: Command line arguments
 * @cmd_mem: Buffer for command
 * @env_vars: Environment variables
 * @tokenCount: Count of tokens
 * @argv: Arguments at opening of shell
 * @close_status: Exit status
 * @commands: Commands to execute
 */
<<<<<<< HEAD
typedef struct shell_vars
{
    char **tokens;
    char *cmd_mem;
    char **env_vars;
    size_t tokenCount;
    char **argv;
    int close_status;
    char **commands;
} shell_t;

/**
 * struct embedded - Struct for the builtin functions
 * @name: Name of builtin command
 * @f: Function for corresponding builtin
 */
typedef struct embedded
{
    char *name;
    void (*f)(shell_t *);
} embedded_t;

/* PATH functions */
int _execute(char *command, shell_t *shell_vars);
char *str_path(char **env_arr);
void exec_curr_dir(shell_t *shell_vars);
void check_path(shell_t *shell_vars);
int is_PATH(char *name);

/* Close function */
void close_shell(shell_t *shell_vars);  // Renamed from close() to avoid conflicts

/* Strtok functions */
unsigned int is_a_match(char c, const char *str);
char *custom_strtok(char *str, const char *delim);

/* Tokenizer function */
char **custom_tokenizer(char *inputBuffer, char *delimiter);

/* Embedded functions */
=======
typedef struct embedded
{
	char *name;
	void (*f)(shell_t *);
} embedded_t;

/* PATH functions */
int _execute(char *command, shell_t *shell_vars);
char *str_path(char **env_arr);
exec_curr_dir(shell_t *shell_vars);
void check_path(shell_t *shell_vars);
int is_PATH(char *name);

/* close function */
void close(shell_t *shell_vars);

/* strtok functions */
unsigned int is_a_match(char c, const char *str);
char *custom_strtok(char *str, const char *delim);

/* tokenizer function */
char **custom_tokenizer(char *inputBuffer, char *delimiter);

/* embedded functions */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
void curr_env(shell_t *shell_vars);
void create_edit_env(shell_t *shell_vars);
void rm_env(shell_t *shell_vars);
void (*embedded(shell_t *shell_vars))(shell_t *shell_vars);

<<<<<<< HEAD
/* Environment functions */
=======
/* environment function */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
char **is_env(char **env_var, char *path);
void env_free(char **env);
char **env_copy(char **environ);
char *new_env(char *name, char *value);
void env_plus(shell_t *shell_vars);

<<<<<<< HEAD
/* Stdlib replacements */
=======
/* stdlib replacements */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

ssize_t str_out(char *str);
int _strlen(char *s);
void str_error(char *str);

char *_strdup(char *replica);
char *int_to_string(unsigned int count);

<<<<<<< HEAD
/* Memory reallocation function */
char **more_mem(char **ptr, size_t *size);

/* Print error function */
void print_error(shell_t *shell_vars, char *err_message);

/* Main function yet to be added */
=======
/* memory reallocation function */
char **more_mem(char **ptr, size_t *size);

/*print error function*/
void print_error(shell_t *shell_vars, char *err_message);

/* main function yet to be added */
>>>>>>> 19b096774c648afb4d06db62340c1737b32a5972
void sig_handler(int sig_handler);
int main(int argc, char **argv, char **environment);

#endif 
