// visuals.c
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* clear the screen by forking & exec’ing clear(1) */
void clear_screen(void)
{
    if (fork() == 0)
    {
        execlp("clear", "clear", NULL);
        exit(1);
    }
    wait(NULL);
}

/* print Pebble ASCII‐art banner */
void init_printout(void)
{
    printf(" ____  _____ ____  ____  _      _      \n");
    printf("|  _ \\| ____| __ )| __ )| |    | |     \n");
    printf("| |_) |  _| |  _ \\|  _ \\| |    | |     \n");
    printf("|  __/| |___| |_) | |_) | |___ | |___  \n");
    printf("|_|   |_____|____/|____/|_____|_____| \n\n");
    printf("By Riley Simmons\n\n");
}
