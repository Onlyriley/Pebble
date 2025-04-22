#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

char *expand_env(const char *arg);

/* add '/bin/' unless it's a ./path */
void add_bin_prefix(char **args)
{
    if (!args[0] || (args[0][0] == '.' && args[0][1] == '/'))
        return;

    char buf[BUFFER_SIZE];
    snprintf(buf, sizeof(buf), "/bin/%s", args[0]);
    strcpy(args[0], buf);
}

/* split input into args[], return count */
int tokenize_command(char *input, char **args)
{
    int i = 0;
    char *tok = strtok(input, " ");
    while (tok && i < NUM_MAX_ARGS - 1)
    {
        args[i++] = expand_env(tok);
        tok = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i;
}

/* helper to remove '<', '>' or '>>' and its target */
void remove_redir(char **args, int i)
{
    free(args[i]);
    free(args[i + 1]);
    args[i] = args[i + 1] = NULL;
}

/* scan and apply any I/O redirection */
void redirection(int argCount, char **args)
{
    for (int i = 0; i < argCount; i++)
    {
        if (!args[i])
            continue;
        if (strcmp(args[i], "<") == 0)
        {
            int in = open(args[i + 1], O_RDONLY);
            dup2(in, STDIN_FILENO);
            close(in);
            remove_redir(args, i);
        }
        else if (strcmp(args[i], ">") == 0)
        {
            int out = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
            dup2(out, STDOUT_FILENO);
            close(out);
            remove_redir(args, i);
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            int out = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
            dup2(out, STDOUT_FILENO);
            close(out);
            remove_redir(args, i);
        }
    }
}

/* fork & exec, handle '&' background and single '|' pipe */
void exec_command(int argCount, char **args)
{
    int background = 0;
    if (argCount > 0 && strcmp(args[argCount - 1], "&") == 0)
    {
        background = 1;
        args[--argCount] = NULL;
    }

    add_bin_prefix(args);
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        return;
    }
    if (pid == 0)
    {
        /* child */
        /* look for a single pipe */
        for (int i = 0; i < argCount; i++)
        {
            if (args[i] && strcmp(args[i], "|") == 0)
            {
                args[i] = NULL;
                int fd[2];
                pipe(fd);

                /* left side */
                if (fork() == 0)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    redirection(i, args);
                    execvp(args[0], args);
                    perror("exec failed");
                    exit(1);
                }

                /* right side */
                char **args2 = &args[i + 1];
                add_bin_prefix(args2);
                if (fork() == 0)
                {
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    redirection(argCount - i - 1, args2);
                    execvp(args2[0], args2);
                    perror("exec failed");
                    exit(1);
                }

                close(fd[0]);
                close(fd[1]);
                wait(NULL);
                wait(NULL);
                exit(0);
            }
        }

        /* no pipe */
        redirection(argCount, args);
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    }
    else
    {
        /* parent */
        if (!background)
            waitpid(pid, NULL, 0);
        else
            printf("Process %d running in background\n", pid);
    }
}

char *expand_env(const char *arg)
{
    if (arg[0] != '$')
        return strdup(arg);
    const char *var = getenv(arg + 1);
    return var ? strdup(var) : strdup("");
}