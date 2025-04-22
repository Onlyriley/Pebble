#include "shell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

char *pebble_completion(const char *text, int state);
char **pebble_completion_generator(const char *text, int start, int end);

int get_command(char *input, size_t size)
{
    rl_attempted_completion_function = pebble_completion_generator;

    char cwd[BUFFER_SIZE];
    getcwd(cwd, sizeof(cwd));
    char prompt[BUFFER_SIZE + 20];
    snprintf(prompt, sizeof(prompt), "\033[1;36mPebble %s>\033[0m ", cwd);
    char *line = readline(prompt);
    if (!line)
        return 1;

    strncpy(input, line, size - 1);
    input[size - 1] = '\0';
    if (*line)
        add_history(line);

    free(line);
    return 0;
}

char **pebble_completion_generator(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, pebble_completion);
}

char *pebble_completion(const char *text, int state)
{
    static DIR *dir;
    static struct dirent *entry;

    if (!state)
    {
        if (dir)
            closedir(dir);
        dir = opendir(".");
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, text, strlen(text)) == 0)
            return strdup(entry->d_name);
    }

    closedir(dir);
    dir = NULL;
    return NULL;
}
