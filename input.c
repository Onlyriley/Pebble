#include "shell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

/* get_command: uses readline for full editing & arrow‑key history */
int get_command(char *input, size_t size)
{
    char *line = readline("Pebble> ");
    if (!line) /* EOF (Ctrl‑D) */
        return 1;

    strncpy(input, line, size - 1);
    input[size - 1] = '\0';

    if (*line) /* non‑empty, add to history */
        add_history(line);

    free(line);
    return 0;
}
