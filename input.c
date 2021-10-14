#include "Project.h"
#include "functions.h"


char* input(int* size) //The function gets a user's input
{
    char ch;
    int i = 0;
    int sizeCommand = 0;
    char* command = (char*)malloc(sizeof(char));
    checkMemoryAllocation(command);

    ch = getchar();
    while (ch != '\n')
    {
        sizeCommand = sizeCommand + 1;
        command = (char*)realloc(command, sizeCommand * sizeof(char));
        checkMemoryAllocation(command);
        command[i] = ch;
        ch = getchar();
        i++;
    }
    command = realloc(command, 100 * sizeof(char));
    checkMemoryAllocation(command);
    command[i] = '\0';
    *size = i;

    return command;

}

int readCommand(char* line, int sizeLine, int* sizeCommand) //The function gets the commend from the user and check which commend he entered.
{
    int i = 0;
    char* command;
    command = (char*)malloc(sizeLine + 1 * sizeof(char));
    checkMemoryAllocation(command);

    while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
    {
        command[i] = line[i];
        i++;
    }
    command[i] = '\0';
    *sizeCommand = i + 2;

    if (strcmp(command, "find-apt") == 0)
    {
        free(command);
        return 0;
    }
    else if (strcmp(command, "add-apt") == 0)
    {
        free(command);
        return 1;
    }
    else if (strcmp(command, "buy-apt") == 0)
    {
        free(command);
        return 2;
    }
    else if (strcmp(command, "delete-apt") == 0)
    {
        free(command);
        return 3;
    }
    else if (strcmp(command, "exit") == 0)
    {
        free(command);
        return 4;
    }
    /*The user press "exit"*/
    else if (strcmp(command, "!!") == 0)
    {
        free(command);
        return 5;
    }

    else if (strcmp(command, "short_history") == 0)
    {
        free(command);
        return 6;
    }
    else if (strcmp(command, "history") == 0)
    {
        free(command);
        return 7;
    }
    else
    {
        free(command);
        return 8;
    }

}