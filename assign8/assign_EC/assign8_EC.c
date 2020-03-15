#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "assign8_EC.h"

int main(int argc, char const *argv[])
{
    long forkpid, fork2pid, waitpidy = 0, pipeid;
    int exitStatus = 0;
    int fdPipe[2];

    if (pipe(fdPipe) == -1)
    {
        printf("pipe not created: %s", strerror(errno));
        exit(-1);
    }

    int i, *num;
    Cammand **cmds = parse_args(argc, argv, num);

    forkpid = fork();

    switch (forkpid)
    {
    case -1:
        printf("fork failed: ");
        break;
    case 0:
        //show_cammand(cmds[0]);
        if (dup2(fdPipe[1], STDOUT_FILENO) == -1)
        {
            printf("Pipe failed: %s", strerror(errno));
            exit(-1);
        }
        close(fdPipe[0]);
        close(fdPipe[1]);
        if (cmds[0]->numArgs == 1)
            cmds[0]->args[0] = "";
        else
        {
            cmds[0]->args[cmds[0]->numArgs - 1] = NULL;
        }
        execvp(cmds[0]->name, cmds[0]->args);

        printf("Child Process did not execute : PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
        exit(-1);
        break;
    default:
        fork2pid = fork();

        switch (fork2pid)
        {
        case -1:
            printf("fork failed: ");
            break;
        case 0:
            if (dup2(fdPipe[0], STDIN_FILENO) == -1)
            {
                printf("Pipe failed: %s", strerror(errno));
                exit(-1);
            }
            close(fdPipe[0]);
            close(fdPipe[1]);
            if (cmds[1]->numArgs == 1)
                cmds[1]->args[0] = "";
            else
            {
                cmds[1]->args[cmds[1]->numArgs - 1] = NULL;
            }
            execvp(cmds[1]->name, cmds[1]->args);

            printf("Child2 Process did not execute : PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
            exit(-1);
            break;
        default:
            close(fdPipe[0]);
            close(fdPipe[1]);

            break;
        }
        /*waitpid = wait(&exitStatus);
        if (waitpid == -1)
            printf("wait failed: ");*/
        break;
    }
    //printf("Parent Process: PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
    for (i = 0; i < *num; i++)
    {
        waitpidy = wait(&exitStatus);
        if (waitpidy == -1)
            printf("wait failed: ");
        //show_cammand(cmds[i]);
        free_cammand(cmds[i]);
    }
    if (cmds != NULL)
        free(cmds);
    return 0;
}
