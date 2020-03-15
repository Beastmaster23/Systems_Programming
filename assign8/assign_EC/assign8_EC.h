#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_CAMMANDS 2
#define MAX_ARGS 3

typedef struct Cammand
{
    char *name;
    char **args;
    int numArgs;
} Cammand;

Cammand *create_cammand(char *name ,int n, char **args)
{
    Cammand *cmd = (Cammand *)malloc(sizeof(Cammand));
    cmd->name=name;
    cmd->args = args;
    cmd->numArgs = n;
    return cmd;
}

void show_cammand(Cammand *cammand)
{
    int i = 0;
    printf("Name: %s, %d\n", cammand->name, cammand->numArgs);
    for (; i < cammand->numArgs; i++)
    {
        printf("arg: %s\n", cammand->args[i]);
    }
}

void free_cammand(Cammand *cammand)
{
    int n = 0;
    if (cammand == NULL)
        return;
    for (; n < cammand->numArgs; n++)
    {
        if (cammand->args[n] != NULL)
            free(cammand->args[n]);
    }

    if (cammand->args != NULL)
        free(cammand->args);
    if (cammand->name != NULL)
        free(cammand->name);
    free(cammand);
}

Cammand **parse_args(int argc, char const *argv[], int *numP)
{
    char *str;
    char **args = (char **)malloc(sizeof(char *) * MAX_ARGS + 1);
    Cammand **cmds = (Cammand **)malloc(sizeof(Cammand *) * MAX_CAMMANDS);
    int i = 1, j = 0, num = 0;
    while (i < argc)
    {
        //getting  arguments and name
        if (argv[i][0] != ',' && j < MAX_ARGS)
        {
            if (j == 0)
            {
                str = (char *)malloc(sizeof(char) * strlen(argv[i]));
                strcpy(str, argv[i]);
            }
            else
            {
                //arguments
                args[j - 1] = (char *)malloc(sizeof(char) * strlen(argv[i]));
                strcpy(args[j - 1], argv[i]);
            }
            j++;
        }

        //create cammand
        if (i == argc - 1 || argv[i][0] == ',')
        {
            if(num>=MAX_CAMMANDS){
                break;
            }
            //args[j-1] = NULL;
            cmds[num] = create_cammand(str, j-1, args);
            //show_cammand(cmds[num]);
            j = 0;
            num++;
            args = (char **)malloc(sizeof(char *) * MAX_ARGS);
        }
        i++;
    }
    *numP = num;
    return cmds;
}
