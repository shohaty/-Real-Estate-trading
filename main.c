#include "project.h"
#include "functions.h"
#include "linkedList.h"

void main()
{
    FILE* file_ptr;
    FILE* file_BinPtr;
    char* command = NULL;
    int sizeOfArray = 0, numOfCommand = 0, sizeOfLine, sizecommand, indexStr1, indexStr2;
    static int numOfApt = 0;
    int aptCode = 1;
    int printIndexHistory, countHistory = 0;
    bool flag = false;
    bool isFileRead = true;
    bool isFileOpen = true;
    int howManyCommands, index = 0;
    int howManyAptBought = 0;
    int* arrOfSizesFromText;
    Apartment* arr_Of_Apt;
    LIST oldHistoryList;
    makeEmptyList(&oldHistoryList);
    char* short_term_history[N];
    arr_Of_Apt = (Apartment*)malloc(sizeof(Apartment));
    checkMemoryAllocation(arr_Of_Apt);
    arrOfSizesFromText = (int*)calloc(N, sizeof(int));
    checkMemoryAllocation(arrOfSizesFromText);
    int whichHistoryCommandNumber, exclamationMarkNum;
    char* str1;
    char* str2;
    file_ptr = fopen("ListCommandsHistory.txt", "r");
    if (file_ptr == NULL)
    {
        file_ptr = fopen("ListCommandsHistory.txt", "w");
        checkFileAllocation(file_ptr);
        fclose(file_ptr);
        isFileRead = false;
    }
    else
        checkFileAllocation(file_ptr);

    file_BinPtr = fopen("AptBinFile.bin", "rb");
    if (file_BinPtr != NULL)
    {
        arr_Of_Apt = readAptFromBinFile(file_BinPtr, &numOfApt,&howManyAptBought);
        fclose(file_BinPtr);
        sizeOfArray = numOfApt;
        aptCode = arr_Of_Apt[numOfApt - 1].aptCode + 1;
    }
    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\nFor reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");

    while (numOfCommand != 4)
    {

        while (file_ptr != NULL && isFileRead)
        {
            command = findCommandFromTextFile(file_ptr, &sizeOfLine, &howManyCommands);
            sizeOfLine = HistoryinsertFromTextFile(command, short_term_history, sizeOfLine, &oldHistoryList);
            if (index < 7)
                arrOfSizesFromText[index] = sizeOfLine;
            countHistory++;
            index++;
            if (howManyCommands == index)
            {
                isFileRead = false;
                fclose(file_ptr);
            }
        }
       
        if (flag == false)
        {
            printf(">>");
            command = input(&sizeOfLine);
        }
        flag = false;
        numOfCommand = readCommand(command, sizeOfLine, &sizecommand);
        switch (numOfCommand)
        {
        case 0://find apt
            Historyinsert(command, short_term_history, sizeOfLine, &oldHistoryList, arrOfSizesFromText);
            countHistory++;
            findApt(arr_Of_Apt, numOfApt, command + sizecommand, sizeOfLine - sizecommand,howManyAptBought);
            printf("\n");
            break;
        case 1://add-apt
            Historyinsert(command, short_term_history, sizeOfLine, &oldHistoryList, arrOfSizesFromText);
            countHistory++;
            sizeOfArray = sizeOfArray * 2 + 1;
            arr_Of_Apt = (Apartment*)realloc(arr_Of_Apt, sizeOfArray * sizeof(Apartment));
            checkMemoryAllocation(arr_Of_Apt);
            addApt(&arr_Of_Apt[numOfApt], command + sizecommand, aptCode);
            aptCode++;
            numOfApt++;
            arr_Of_Apt = (Apartment*)realloc(arr_Of_Apt, numOfApt * sizeof(Apartment));
            checkMemoryAllocation(arr_Of_Apt);
            break;
        case 2://buy-apt 
            Historyinsert(command, short_term_history, sizeOfLine, &oldHistoryList, arrOfSizesFromText);
            countHistory++;
            buyApt(arr_Of_Apt, numOfApt, command + sizecommand - 1);
            numOfApt -= 1;
            howManyAptBought++;
            break;
        case 3://delete-apt
            Historyinsert(command, short_term_history, sizeOfLine, &oldHistoryList, arrOfSizesFromText);
            countHistory++;
            deleteAptByTime(arr_Of_Apt, &sizeOfArray, command + sizecommand); 
            break;
        case 4://exit
            addToTextFile(oldHistoryList, short_term_history, countHistory, file_ptr);
            addToBinFile(numOfApt, arr_Of_Apt,howManyAptBought);
            printf("bye bye\n");
            break;
        case 5: //!!
            command = applyLastCommand(short_term_history, &sizeOfLine, countHistory);
            flag = true;
            break;
        case 6://print short history
            if(countHistory<=7)
            printIndexHistory = 1;
            else
            {
                printIndexHistory = countHistory - N+1;
            }
            PrintShortHistory(short_term_history, countHistory, printIndexHistory);
            break;
        case 7:
            printIndexHistory = PrintHistory(oldHistoryList);
            PrintShortHistory(short_term_history, countHistory, printIndexHistory);
            break;

        default:
            exclamationMarkNum = readHistoryCommand(command);
            switch (exclamationMarkNum)
            {
            case 0://only !<num>
                whichHistoryCommandNumber = atoi(command + 1);
                applyExactCommand(oldHistoryList, short_term_history, &sizeOfLine, countHistory, whichHistoryCommandNumber, &command);
                break;
            case 1://!<num>^str1^str2
                str1 = (char*)malloc(MAX_ACTION * sizeof(char));
                checkMemoryAllocation(str1);
                str2 = (char*)malloc(MAX_ACTION * sizeof(char));
                checkMemoryAllocation(str2);

                str1 = disassembleCommand(command, &indexStr1);
                str2 = disassembleCommand(command, &indexStr2);
                str1 = realloc(str1, indexStr1 * sizeof(char));
                checkMemoryAllocation(str1);
                str1[indexStr1] = '\0';
                str2 = realloc(str2, indexStr2 + 3 * sizeof(char));
                checkMemoryAllocation(str2);
                str2[indexStr2] = '\0';
                whichHistoryCommandNumber = whichHistoryCommandNumberTranslate(command);
                applyExactCommand(oldHistoryList, short_term_history, &sizeOfLine, countHistory, whichHistoryCommandNumber, &command);
                replaceStringFromCommand(&command, &sizeOfLine, str1, str2);
                break;
            }

            flag = true;

            break;
        }


    }
}

void printApt(Apartment apt)//print function
{
    printf("Apt details:\n");
    printf("Code: %d\n", apt.aptCode);
    printf("Address: %s\n", apt.address);
    printf("Number of rooms: %d\n", apt.numOfRooms);
    printf("Price: %d\n", apt.price);
    printf("Entry date: %d.%d.%d\n", apt.enterDate[0], apt.enterDate[1], apt.enterDate[2]);
    printf("Database entry date: %s\n", ctime(&(apt.addingDay)));
}


void checkMemoryAllocation(void* ptr)
{

    if (ptr == NULL)
    {
        printf("Memory Allocation ERROR");
        exit(-1);
    }
}




