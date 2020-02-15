#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "assign8.h"

int main(int argc, char const *argv[])
{
    long forkpid;
    long waitpid;
    int exitStatus;

    int i, *num;
    Cammand **cmds = parse_args(argc, argv, num);

    for (i = 0; i < *num; i++)
    {

        forkpid = fork();

        switch (forkpid)
        {
        case -1:
            printf("fork failed: ");
            break;
        case 0:
            show_cammand(cmds[i]);
            execvp(cmds[i]->name, cmds[i]->args);
            
            printf("Child Process did not execute : PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
            exit(-1);
            break;
        default:
            waitpid = wait(&exitStatus);
            if (waitpid == -1)
                printf("wait failed: ");
            break;
        }
    }
    //printf("Parent Process: PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
    for (i = 0; i < *num; i++)
    {
        free_cammand(cmds[i]);
    }
    if (cmds != NULL)
        free(cmds);
    return 0;
}
