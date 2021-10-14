#include "Project.h"
#include "functions.h"

void Historyinsert(char* command, char* short_term_history[N], int sizeOfLine, LIST* oldHistoryList, int* arrOfSizesFromText)// The function inserets the history into the short-term array and the old list
{

    static int i = N - 1;
    int j = N - 1, k = 0;
    static int sizeArray[N];

    if (arrOfSizesFromText != NULL)
    {
        while (k < N && arrOfSizesFromText[0] != 0)
        {
            sizeArray[k] = arrOfSizesFromText[k];
            k++;
            i -= 1;
        }
    }


    if (i >= 0)
    {
        short_term_history[i] = (char*)malloc(sizeOfLine+2 * sizeof(char));
        checkMemoryAllocation(short_term_history[i]);
        strcpy(short_term_history[i], command);
        sizeArray[i] = sizeOfLine;
        i--;
    }
    else
    {
        insertDataToHeadList(oldHistoryList, short_term_history[N - 1], sizeArray[N - 1]);
  
        while (j > 0)
        {
            short_term_history[j] = realloc(short_term_history[j], 100 * sizeof(char));//we weren't able to decrease the size of the realloc due to unexpected behavior. Thanks 
            checkMemoryAllocation(short_term_history[j]);
            strcpy(short_term_history[j], short_term_history[j - 1]);
            sizeArray[j] = sizeArray[j - 1];
            j -= 1;
        }
        short_term_history[0] = realloc(short_term_history[0], sizeOfLine+2 * sizeof(char));
        checkMemoryAllocation(short_term_history[0]);
        strcpy(short_term_history[0], command);
        sizeArray[0] = sizeOfLine;
    }
}

void PrintShortHistory(char* short_term_history[N], int howManyCommands, int printIndex)
{
    int i, j;
    if (howManyCommands < N)
        j = N - howManyCommands;
    else
        j = 0;

    for (i = N - 1;i >= j;i--)
    {
        printf("%d: %s", printIndex, short_term_history[i]);
        printIndex++;
        printf("\n");
    }
}
int PrintHistory(LIST oldHistoryList)
{
    int index = 1;
    LIST resList;
    ListNode* curr;
    curr = oldHistoryList.head;
    makeEmptyList(&resList);
    while (curr != NULL)
    {
        insertDataToHeadList(&resList, curr->command,strlen(curr->command)+1);
        curr = curr->next;
    }
    printList(resList, &index);
    return index;
}