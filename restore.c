#include "Project.h"
#include "functions.h"


char* applyLastCommand(char* short_term_history[N], int* sizeOfLine, int countHistory)// !!
{
    int index;
    if (countHistory < N)
        index = N - countHistory;
    else
        index = 0;
    *sizeOfLine = strlen(short_term_history[index])+1;
    return short_term_history[index];
}


int readHistoryCommand(char* command) //Check if there is ^ in the command to check if it is !<num> or !<num>^str1^str2
{
    char mark = '^';
    int i = 0;
    while (command[i] != '\0')
    {
        if (command[i] == mark)
            return 1;
        else
            i++;
    }
    return 0;

}
int whichHistoryCommandNumberTranslate(char* command)
{
    int res = 0, i = 1;

    while (command[i] != '^')
    {
        res = res * 10 + (int)command[i] - '0';
        i++;
    }

    return res;
}

void applyExactCommand(LIST oldHistoryList, char* short_term_history[N], int* sizeOfLine, int countHistory, int whichHistoryCommandNumber, char** command)//The function finds the exact command we want to apply again from the history. 
{
    int index;
    if (countHistory <= N)
    {
        index = N - whichHistoryCommandNumber;
        *sizeOfLine = strlen(short_term_history[index]);
        strcpy(*command, short_term_history[index]);
    }
    else
    {
        index = countHistory - whichHistoryCommandNumber;
        if (index < 7)
        {
            *sizeOfLine = strlen(short_term_history[index]);
            strcpy(*command, short_term_history[index]);
        }
        else
        {
            ListNode* curr = oldHistoryList.head;
            int i = 1;
            while (i < whichHistoryCommandNumber)
            {
                curr = curr->next;
                i++;
            }
            *sizeOfLine = strlen(curr->command);
            strcpy(*command, curr->command);
        }
    }
}
char* disassembleCommand(char* command, int* sizeStr)//The function disassemble the str from the command
{

    static int i = 0, counter = 0;
    int localsize = 0, j = 0;
    char* tempStr = (char*)malloc(30 * sizeof(char));
    checkMemoryAllocation(tempStr);

    while (command[i] != '^')
        i++;
    i++;

    while (command[i] != '^' && command[i] != '\0')
    {
        localsize++;
        tempStr[j] = command[i];
        j++;
        i++;
    }
    *sizeStr = j;
    counter++;
    if (counter == 2)
    {
        i = 0;
        counter = 0;
    }
    return tempStr;


}
void replaceStringFromCommand(char** command, int* sizeOfLine, char* str1, char* str2)
{
    int sizeCommand, whichCommand;
    whichCommand = readCommand(*command, sizeOfLine, &sizeCommand);
    *command = replaceString(*command, sizeCommand, sizeOfLine, str1, str2);
}
char* replaceString(char* command, int sizeCommand, int* sizeOfLine, char* str1, char* str2)
{
    int stringLen, subLen, newLen;
    int i = 0, j, k;
    int flag = 0, start, end;
    stringLen = strlen(command);
    subLen = strlen(str1);
    newLen = strlen(str2);

    for (i = 0;i < stringLen;i++)
    {
        flag = 0;
        start = i;
        for (j = 0;command[i] == str1[j];j++, i++)
            if (j == subLen - 1)
                flag = 1;
        end = i;
        if (flag == 0)
            i -= j;
        else
        {
            for (j = start;j < end;j++)
            {
                for (k = start;k < stringLen;k++)
                    command[k] = command[k + 1];
                stringLen--;
                i--;
            }

            for (j = start;j < start + newLen;j++)
            {
                for (k = stringLen;k >= j;k--)
                    command[k + 1] = command[k];
                command[j] = str2[j - start];
                stringLen++;
                i++;
            }
        }
    }
    *sizeOfLine = strlen(command) + 1;
    command[*sizeOfLine] = '\0';
    return command;
}

