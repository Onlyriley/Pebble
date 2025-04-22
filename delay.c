#include "shell.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* node for queued commands */
typedef struct DelayedCommand
{
    char **args;
    int argCount;
    time_t execTime;
    struct DelayedCommand *next;
} DelayedCommand;

static DelayedCommand *head = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* schedule a command after 'delay' seconds */
void add_delayed_command(char **args, int delay)
{
    DelayedCommand *cmd = malloc(sizeof(*cmd));
    /* count & copy args */
    int n = 0;
    while (args[n])
        n++;
    cmd->argCount = n;
    cmd->args = malloc((n + 1) * sizeof(char *));
    for (int i = 0; i < n; i++)
        cmd->args[i] = strdup(args[i]);
    cmd->args[n] = NULL;

    cmd->execTime = time(NULL) + delay;
    cmd->next = NULL;

    pthread_mutex_lock(&mutex);
    if (!head || head->execTime > cmd->execTime)
    {
        cmd->next = head;
        head = cmd;
    }
    else
    {
        DelayedCommand *cur = head;
        while (cur->next && cur->next->execTime <= cmd->execTime)
            cur = cur->next;
        cmd->next = cur->next;
        cur->next = cmd;
    }
    pthread_mutex_unlock(&mutex);
}

/* background loop to execute due commands */
void *delay_loop(void *arg)
{
    (void)arg;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (head && head->execTime <= time(NULL))
        {
            DelayedCommand *cmd = head;
            head = head->next;
            pthread_mutex_unlock(&mutex);

            exec_command(cmd->argCount, cmd->args);

            for (int i = 0; i < cmd->argCount; i++)
                free(cmd->args[i]);
            free(cmd->args);
            free(cmd);

            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
