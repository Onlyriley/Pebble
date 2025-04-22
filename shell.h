#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

#define NUM_MAX_ARGS 64
#define BUFFER_SIZE 256

/* screen & banner */
void clear_screen(void);
void init_printout(void);

/* input & history */
int get_command(char *input, size_t size);

/* parsing & helpers */
int tokenize_command(char *input, char **args);
void add_bin_prefix(char **args);

/* execution */
void exec_command(int argCount, char **args);
void redirection(int argCount, char **args);
void remove_redir(char **args, int i);

/* delay */
void add_delayed_command(char **args, int delay);
void *delay_loop(void *arg);

#endif /* SHELL_H */
