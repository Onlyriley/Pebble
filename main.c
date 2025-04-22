#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/* Main program loop */
int main(void)
{
    char input[BUFFER_SIZE];
    char *args[NUM_MAX_ARGS];
    int argCount;

    clear_screen();
    init_printout();
    chdir(getenv("HOME"));

    /* start background thread for delayed commands */
    pthread_t tid;
    pthread_create(&tid, NULL, delay_loop, NULL);

    while (1)
    {
        /* prompt and read a line */
        if (get_command(input, sizeof(input)) == 1)
            break;

        argCount = tokenize_command(input, args);
        if (argCount == 0)
            continue;

        /* built‑ins */
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL || chdir(args[1]) == -1)
            {
                if (args[1] && args[1][0] == '~')
                    chdir(getenv("HOME"));
                else
                    perror("cd failed");
            }
        }
        else if (strcmp(args[0], "delay") == 0 && argCount >= 3)
        {
            int d = atoi(args[1]);
            add_delayed_command(args + 2, d);
        }
        else
        {
            exec_command(argCount, args);
        }
    }

    return 0;
}
